#include "config_parser.h"

XrayConfig::XrayConfig()
{
    this->init_base_config(XRAY_BASE_CONFIG_PATH);

    this->init_config(XRAY_CONFIG_PATH);

    this->init_save_configs(XRAY_SAVE_CONFIGS_PATH);
}

void XrayConfig::init_base_config(QString config_path)
{
    this->base_config.reset(new QFile());

    this->base_config->setFileName(config_path);
    if (!this->base_config->open(QIODevice::ReadOnly) &&
        QFile::exists(config_path))
        return;

    this->base_config->close();
}

void XrayConfig::init_config(QString config_path)
{
    this->run_config.reset(new QFile());

    this->run_config->setFileName(config_path);
    if (!this->run_config->open(QIODevice::ReadWrite | QIODevice::Text)) {
        return;
    }

    if (0 == this->run_config->bytesAvailable()) {
        this->base_config->open(QIODevice::ReadOnly);
        this->run_config->write(this->base_config->readAll());
        this->base_config->close();
        this->run_config->seek(0);
    }

    QJsonParseError parse_error;
    QJsonDocument json_doc =
        QJsonDocument::fromJson(this->run_config->readAll(), &parse_error);
    if (parse_error.error != QJsonParseError::NoError) {
        this->run_config->close();
        return;
    }

    if (!json_doc.isObject() || json_doc.isEmpty()) {
        this->run_config->close();
        return;
    }

    this->run_config_json.reset(new QJsonObject(json_doc.object()));

    this->run_config->close();
}

void XrayConfig::init_save_configs(QString config_path)
{
    this->save_configs_file.reset(new QFile());

    this->save_configs_file->setFileName(config_path);
    if (!this->save_configs_file->open(QIODevice::ReadWrite) &&
        QFile::exists(config_path))
        return;

    QJsonParseError parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(
        this->save_configs_file->readAll(), &parse_error);
    if (parse_error.error != QJsonParseError::NoError) {
        this->save_configs_file->close();
        return;
    }

    if (!json_doc.isObject()) {
        this->run_config->close();
        return;
    }

    if (json_doc.isEmpty()) {
        this->save_configs_json.reset(new QJsonObject());
    } else {
        this->save_configs_json.reset(new QJsonObject(json_doc.object()));
        for (QJsonObject::const_iterator iter =
                 this->save_configs_json->constBegin();
             iter <= this->save_configs_json->constEnd(); iter++) {
            this->save_configs.append(iter.key());
        }
    }

    this->save_configs_file->close();
}

QStringList XrayConfig::get_save_configs()
{
    return this->save_configs;
}

void XrayConfig::choose_config(QString config_name)
{
    if (!this->save_configs.contains(config_name))
        return;
    QJsonArray connection = (*this->save_configs_json)[config_name].toArray();

    if (!this->run_config->open(QIODevice::ReadWrite | QIODevice::Text)) {
        return;
    }

    if (this->run_config_json->contains("outbounds"))
        this->run_config_json->remove("outbounds");
    this->run_config_json->insert("outbounds", connection);
}

void XrayConfig::import_config(QString file_path)
{
    QFile import_config_file(file_path);
    if (!import_config_file.open(QIODevice::ReadOnly) &&
        QFile::exists(file_path))
        return;

    QJsonParseError parse_error;
    QJsonDocument import_json_doc =
        QJsonDocument::fromJson(import_config_file.readAll(), &parse_error);
    if (parse_error.error != QJsonParseError::NoError) {
        import_config_file.close();
        return;
    }

    if (!import_json_doc.isObject() || import_json_doc.isEmpty()) {
        import_config_file.close();
        return;
    }

    QJsonArray outbounds = import_json_doc.object()["outbounds"].toArray();
    QString config_name = QRegularExpression("([A-Za-z0-9_-]+).json")
                              .match(file_path)
                              .captured(1);

    if (this->save_configs.contains(config_name)) {
        import_config_file.close();
        return;
    }

    this->save_configs.append(config_name);

    this->save_configs_json->insert(config_name, outbounds);

    if (!this->save_configs_file->open(QIODevice::ReadWrite |
                                       QIODevice::Text)) {
        import_config_file.close();
        return;
    }

    QJsonDocument json_doc(*this->save_configs_json);
    this->save_configs_file->write(json_doc.toJson(QJsonDocument::Indented));

    this->save_configs_file->close();
    import_config_file.close();

    emit config_imported();
}
