#include <max5494_max5499/Arduino.h>

#include <Arduino.h>
#include <SPI.h>

#define TEST_TOLERANCE ((double)1024 / 20) /* ±5% */
#define TEST_STOP()                          \
    do                                       \
    {                                        \
        Serial.println("Assertion failed."); \
        digitalWrite(LED_BUILTIN, HIGH);     \
    } while (true)
#define TEST_ASSERT_EQUAL_WITH_TOLERANCE(expected, actual)                                  \
    do                                                                                      \
    {                                                                                       \
        if ((actual) < (expected)-TEST_TOLERANCE || (expected) + TEST_TOLERANCE < (actual)) \
        {                                                                                   \
            TEST_STOP();                                                                    \
        }                                                                                   \
    } while (0)

static const pin_size_t PIN_SPI_SCK = 2;
static const pin_size_t PIN_SPI_TX = 3;
static const pin_size_t PIN_SPI_CS = 5;
static const pin_size_t PIN_W1 = 26;
static const pin_size_t PIN_W2 = 27;

static MAX5494_MAX5499 max5494(&SPI, PIN_SPI_CS);

void setup()
{
    Serial.begin();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(PIN_W1, INPUT);
    pinMode(PIN_W2, INPUT);

    pinMode(PIN_SPI_CS, OUTPUT);
    digitalWrite(PIN_SPI_CS, HIGH);

    SPI.setCS(PIN_SPI_CS);
    SPI.setSCK(PIN_SPI_SCK);
    SPI.setTX(PIN_SPI_TX);
    SPI.begin();

    delay(15'000);

    int result;

    max5494.writeWiperRegister1(0);
    delay(1);
    Serial.println("max5494.writeWiperRegister1(0);");
    Serial.println(result = analogRead(PIN_W1));
    TEST_ASSERT_EQUAL_WITH_TOLERANCE(0, result);

    max5494.writeWiperRegister1(0b11'11111111);
    delay(1);
    Serial.println("max5494.writeWiperRegister1(0b11'11111111);");
    Serial.println(result = analogRead(PIN_W1));
    TEST_ASSERT_EQUAL_WITH_TOLERANCE(1024, result);

    max5494.writeWiperRegister2(0);
    delay(1);
    Serial.println("max5494.writeWiperRegister2(0);");
    Serial.println(result = analogRead(PIN_W2));
    TEST_ASSERT_EQUAL_WITH_TOLERANCE(0, result);

    max5494.writeWiperRegister2(0b11'11111111);
    delay(1);
    Serial.println("max5494.writeWiperRegister2(0b11'11111111);");
    Serial.println(result = analogRead(PIN_W2));
    TEST_ASSERT_EQUAL_WITH_TOLERANCE(1024, result);

    Serial.println("OK");
}

void loop()
{
}