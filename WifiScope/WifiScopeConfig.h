
#define VERSION "0.1"

// how long to wait for a wifi connection before starting the server
#define CONFIG_WIFI_TIMEOUT_S 40

// allow cross-site scripting (javascript form other sites to access the device)?
// (useful for testing/debugging)
#define FEATURE_ALLOW_CORS

// use WIFI settings (SSID, password, ...) from EEPROM or hardcoded settings?
#define FEATURE_USE_EEPROM_CONFIG

// the following settings are only relevant when the EEPROM config is disabled
#ifndef FEATURE_USE_EEPROM_CONFIG

  // hardcoded SSID for the WIFI network
  #define CONFIG_WIFI_SSID     "foo"

  // hardcoded password for the WIFI network
  #define CONFIG_WIFI_PASSWORD "bar"

  // hardcoded hostname for this device
  #define CONFIG_WIFI_HOSTNAME "hameg"

  // port number for the web server
  #define CONFIG_WEB_PORT      80

#endif
