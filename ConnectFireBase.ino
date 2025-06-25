#define ENABLE_USER_AUTH
#define ENABLE_DATABASE

#include <FirebaseClient.h>
#include "ExampleFunctions.h" // Provides the functions used in the examples.

// WiFi cấu hình
#define WIFI_SSID "Akine"
#define WIFI_PASSWORD "26061304"

#define API_KEY "DxMxtItdJgdmHjmGiN6sPTlwM6XfBUJNmeqLk7D7"
#define USER_EMAIL "xuanthinhkl1@gmail.com"
#define USER_PASSWORD "515515"
#define DATABASE_URL "weather-station-iot-ded0e-default-rtdb.asia-southeast1.firebasedatabase.app"

void processData(AsyncResult &aResult);
void get_async();
void get_async2();
void get_await();
void create_dummy_data();

SSL_CLIENT ssl_client;

using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client);

UserAuth user_auth(API_KEY, USER_EMAIL, USER_PASSWORD, 3000 /* expire period in seconds (<3600) */);
FirebaseApp app;
RealtimeDatabase Database;
AsyncResult databaseResult;

bool taskComplete = false;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

    set_ssl_client_insecure_and_buffer(ssl_client);

    Serial.println("Initializing app...");
    initializeApp(aClient, app, getAuth(user_auth), auth_debug_print, "🔐 authTask");

    // Or intialize the app and wait.
    // initializeApp(aClient, app, getAuth(user_auth), 120 * 1000, auth_debug_print);

    app.getApp<RealtimeDatabase>(Database);

    Database.url(DATABASE_URL);

    // Đợi Firebase kết nối
    unsigned long timeout = millis() + 10000;
    while (!app.ready() && millis() < timeout)
    {
        app.loop();
        delay(100);
    }

    if (app.ready())
        Serial.println("Kết nối Firebase thành công!");
    else
        Serial.println("Kết nối Firebase thất bại (timeout hoặc cấu hình sai)");
}

void loop() 
{
    // To maintain the authentication and async tasks
    app.loop();
}