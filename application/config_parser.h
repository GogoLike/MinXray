#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <memory>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#ifndef XRAY_BASE_CONFIG_PATH
#define XRAY_BASE_CONFIG_PATH "base_config.json"
#endif

#ifndef XRAY_CONFIG_PATH
#define XRAY_CONFIG_PATH "config.json"
#endif

#ifndef XRAY_SAVE_CONFIGS_PATH
#define XRAY_SAVE_CONFIGS_PATH "save_configs.json"
#endif

class XrayConfig : public QObject
{
    //! Qt specific macro for Signals and Slots work
    // cppcheck-suppress unknownMacro
    Q_OBJECT

public:
    explicit XrayConfig();

    QStringList get_save_configs();
    void choose_config(QString config_name);

private:
    // Object for basic config read
    std::unique_ptr<QFile> base_config;

    // Objects for work with complete xray config for run xray-core
    std::unique_ptr<QFile> run_config;
    std::unique_ptr<QJsonObject> run_config_json;

    std::unique_ptr<QFile> save_configs_file;
    std::unique_ptr<QJsonObject> save_configs_json;
    QStringList save_configs;

    void init_base_config(QString config_path);
    void init_config(QString config_path);
    void init_save_configs(QString config_path);

    //! Qt specific macro
    // cppcheck-suppress unknownMacro
signals:
    void config_imported();

    //! Qt specific macro
    // cppcheck-suppress unknownMacro
public slots:
    void import_config(QString file_path);
};

#endif
