#include <EEPROM.h>

#define LED_PIN_1 9
#define LED_PIN_2 8
#define LED_PIN_3 7
#define LED_PIN_4 6

const char clear[] PROGMEM =
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "\n";
const char intro[] PROGMEM =
    "====================================================================================================================\n"
    "                                                 #####                                             \n"
    "               ###   ##    #    ### ##  #####   ##   ##   ### ##  ## #####  ###   #### #####  #### \n"
    "                ### ###   ###    ## #    ##     #  ## #    ##  ## #   ##   ##  # ##  #  ##   ##  # \n"
    "                # ## ##  #  ##   ###     ####   # # # #    ##  ####   #### ##  # ####   #### ##    \n"
    "                # ## ##  #####   ####    ##     # ####     ##  ####   ##   ##  #  ####  ##   ##    \n"
    "                # ## ##  #  ##   ## ##   ## #   ##         ##  # ##   ##   ##  # #  ##  ## # ##  # \n"
    "               ##  # ## ##  ### ### ### #####    ####     ### ##  #  ####   ###  ####  #####  ###  \n"
    "====================================================================================================================\n"
    "                          \" HELLO, WELCOME TO HACKING BADGE IN DUKYOUNG HIGH SCHOOL \"\n"
    "====================================================================================================================\n"
    "                                게임 방법을 모르겠다면, 'help'를 입력하고 엔터를 입력해주세요!\n"
    "\n"
    "                                      문제 1 : Decoding This Word\n"
    "                                      문제 2 : CQ CQ CQ\n"
    "                                      문제 3 : ZOMBIE\n"
    "                                      문제 4 : King Carsar\n"
    "                                      clear : 시리얼 모니터의 모든 내용이 사라집니다\n"
    "                                      help  : 게임 설명과 FLAG 형식이 들어있습니다\n"
    "====================================================================================================================\n";

const char gameRule[] PROGMEM =
    " ---------------------------------------------------<< 게임 방법 >>---------------------------------------------------\n"
    "                               1. 풀고자 하는 문제의 번호를 입력한다. (1~4번 순서대로 풀어주세요!)\n"
    "                               2. 출제된 문제를 풀이하고 FLAG 형식에 맞춰 정답을 입력한다.\n"
    "                               3. 정답을 맞춘다면 번호에 맞는 LED에 불이 켜진다!\n"
    "                               4. 게임 진입 후, 나가고 싶다면 문제 실행 후 \'exit\'를 입력한다.\n"
    "====================================================================================================================\n"
    "                                          FLAG 형식은 \"DYHS{...}\" 입니다.\n"
    "                                      (예시. 정답이 1234 라면, DYHS{1234}으로 입력)\n"
    "====================================================================================================================\n"
    "\n"
    "# #   ###  ##   #       ### ###    #     #### ### ##  ### ##  ##  ####   ##### ### ###   ## #####           ##   # #\n"
    "# #    ##  ##   #        ##  #    ###   ##  #  ## #    ##  ## #  ##  #   ### #  ##  ### ###  ##             ##   # #\n"
    "       ## #### #  ###    #####   #  ##  ##     ###     ##  ####  ##       ##    ##  # ## ##  ####    ## #   #\n"
    "       ##  ##     ##     ##  #   #####  ##     ####    ##  ####  ## ##    ##    ##  # ## ##  ##     # ##\n"
    "       ##  ##      ##    ##  #   #  ##  ##  #  ## ##   ##  # ##  ##  #    ##    ##  # ## ##  ## #           #\n"
    "      ###   ##    ###   ### ### ##  ###  ###  ### ### ### ##  #   ####   ####  ### ##  # ## #####           #\n"
    "\n"
    "                                           \" 지금 당장 뱃지 해킹에 도전하세요! \"\n"
    "                                         (\'dyhs\'를 입력하여 처음으로 돌아가세요.)\n"
    "====================================================================================================================\n";

const char p1[] PROGMEM =
    "====================================================================================================================\n"
    " ------------------------------------------<  문제 01. Decoding This Word  >---------------------------------------- \n"
    "|                                                                                                                  |\n"
    "|                    아래 읽을 수 없는 문자열이 있어요. 해커한테 물어보니, 알아볼 수 없게 문자 인코딩을 바꿔놨다고 해요.                  |\n"
    "|                            문자열을 읽거나 알아볼 수 있게 변환해야 해요! 어떻게 하면 변환할 수 있을까요?                           |\n"
    "|                                                                                                                  |\n"
    " -------------------------------------------------<  인코딩 된 문자열  >----------------------------------------------- \n"
    "|                                  RFlIU3tEMF9ZMHVfS24wV19XaEBUXzNuQzBkSW5HXzFzP30                                 |\n"
    " ------------------------------------------------------------------------------------------------------------------ \n"
    "====================================================================================================================\n";

const char p2[] PROGMEM =
    "====================================================================================================================\n"
    " -----------------------------------------------<  문제 02. CQ CQ CQ  >--------------------------------------------- \n"
    "|                                                                                                                  |\n"
    "|                          아래 보면 점과 선으로 이루어진 문자열이 있어요. 통신에서 사용하는 부호라고 하던데...                        |\n"
    "|                         아래 문자열을 알아볼 수 있는 평문으로 변환해서 FLAG 형식에 맞춰 정답을 입력해주세요!                        |\n"
    "|                                                                                                                  |\n"
    " ---------------------------------------------<  점과 선으로 이루어진 문자열  >------------------------------------------- \n"
    "|                         -.-. --.- -.-. --.- -.-. --.- -.. . -- .- -.- . -- .- -.- . .- .-.                       |\n"
    " ------------------------------------------------------------------------------------------------------------------ \n"
    "====================================================================================================================\n";

const char p3[] PROGMEM =
    "====================================================================================================================\n"
    " ------------------------------------------------<  문제 03. ZOMBIE  >---------------------------------------------- \n"
    "|                                                                                                                  |\n"
    "|                      마인크래프트를 하다가 좀비를 만나게 되었어요! 좀비를 처치했더니 아래와 같은 숫자가 나타났어요.                     |\n"
    "|                                숫자를 16진수와 변환하면 나온다고 하는데.. 어떻게 표현해야할까요?                                |\n"
    "|                                                                                                                  |\n"
    " -------------------------------------------------<  알 수 없는 숫자  >----------------------------------------------- \n"
    "|                                                    3735928559                                                    |\n"
    " ------------------------------------------------------------------------------------------------------------------ \n"
    "====================================================================================================================\n";

const char p4[] PROGMEM =
    "====================================================================================================================\n"
    " ----------------------------------------------<  문제 04. King Caesar  >------------------------------------------- \n"
    "|                                                                                                                  |\n"
    "|       예전에 로마 제국에 카이사르 라는 왕이 살았어요. 카이사르 왕은 동맹군과 소통하는것을 좋아했는데 특히 애용하던 암호화 알고리즘이 있어요.      |\n"
    "|   아래 문자열은 카이사르 왕이 애용한 암호화 알고리즘으로 암호화한 암호문이에요. 사용된 암호화 알고리즘을 찾고 취약점을 공격해서 FLAG를 얻으세요!   |\n"
    "|                                                                                                                  |\n"
    " -------------------------------------------------<  암호화 된 암호문  >----------------------------------------------- \n"
    "|                                 TOXI{S0dwh@jK1QjY0dI_O0k_x@sA3T_@11_Jx3i3_t3lYs3i}                               |\n"
    " ------------------------------------------------------------------------------------------------------------------ \n"
    "====================================================================================================================\n";

const char allSolve[] PROGMEM =
    "        ### ###    #     #### ### ##  ##### #####    ##### ### ##  ## ###  #### ### ### ##### #####    ##        \n"
    "         ##  #    ###   ##  #  ## #    ##    ##  #    ##    ##  ## #   ## ##  #  ##  #   ##    ##  #   ##        \n"
    " ######  #####   #  ##  ##     ###     ####  ##  #    ####  ##  ####   ## ####   #####   ####  ##  #   #  ###### \n"
    "######   ##  #   #####  ##     ####    ##    ##  #    ##    ##  ####   ##  ####  ##  #   ##    ##  #     ######  \n"
    "         ##  #   #  ##  ##  #  ## ##   ## #  ##  #    ##    ##  # ##   ## #  ##  ##  #   ## #  ##  #   #         \n"
    "        ### ### ##  ###  ###  ### ### ##### #####    ####  ### ##  #  ### ####  ### ### ##### #####    #         \n"
    "\n"
    "       ###   ## ###  ####  #### ###  ###  ##  ##    ####  ###  ###   ## ####  ####  ##### ##### #####   ##       \n"
    "        ### ###  ## ##  # ##  #  ## ##  #  ## #    ##  # ##  #  ### ###  ## #  ##    ##   ### #  ##     ##       \n"
    "        # ## ##  ## ####  ####   ## ##  #  ####    ##    ##  #  # ## ##  ## #  ##    ####  ##    ####   #        \n"
    "        # ## ##  ##  ####  ####  ## ##  #  ####    ##    ##  #  # ## ##  ###   ##    ##    ##    ##              \n"
    "        # ## ##  ## #  ## #  ##  ## ##  #  # ##    ##  # ##  #  # ## ##  ##    ## #  ## #  ##    ## #   #        \n"
    "       ##  # ## ### ####  ####  ###  ###  ##  #     ###   ###  ##  # ## ####  ##### ##### ####  #####   #        \n"
    "=================================================================================================================\n"
    "                                 DY Hacking Badge을 성공적으로 해킹하였습니다! 축하합니다!                                 \n"
    "                          You successfully hacked the DY Hacking Badge! Congratulations!                         \n"
    "=================================================================================================================\n";

const int eepromAddresses[4] = {0, 1, 2, 3};

void resetEEPROM()
{
  for (int i = 0; i < 4; i++)
  {
    EEPROM.update(eepromAddresses[i], 0); // 모든 LED 상태를 끈 상태(0)로 초기화
  }
}

int statusEEPROM(int idx)
{
  if (EEPROM.read(eepromAddresses[idx]) == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int sumEEPROM()
{
  int res = 0;
  for (int i = 0; i < 4; i++)
  {
    res = res + statusEEPROM(i);
  }
  return res;
}

void setup()
{
  Serial.begin(4800);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);

  digitalWrite(LED_PIN_1, EEPROM.read(eepromAddresses[0]) ? HIGH : LOW);
  digitalWrite(LED_PIN_2, EEPROM.read(eepromAddresses[1]) ? HIGH : LOW);
  digitalWrite(LED_PIN_3, EEPROM.read(eepromAddresses[2]) ? HIGH : LOW);
  digitalWrite(LED_PIN_4, EEPROM.read(eepromAddresses[3]) ? HIGH : LOW);

  for(int i = 9; i >= 6; i--) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW);
  }
  for(int i = 6; i <= 9; i++) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW);
  }
}

bool main_page = false;

void loop()
{
  String input = Serial.readStringUntil('\n');
  if (Serial)
  {
    input.trim();
    if(input == "") {
      if (EEPROM.read(eepromAddresses[0]) == 1 && EEPROM.read(eepromAddresses[1]) == 1 && EEPROM.read(eepromAddresses[2]) == 1 && EEPROM.read(eepromAddresses[3]) == 1) {
        for(int i = 9; i >= 6; i--) {
          digitalWrite(i,HIGH);
          delay(50);
          digitalWrite(i,LOW);
        }
        for(int i = 6; i <= 9; i++) {
          digitalWrite(i,HIGH);
          delay(50);
          digitalWrite(i,LOW);
        }
      }
    }
    else if (input == "reset")
    {
      for (int i = 0; i < 3; i++)
      {
        Serial.println();
      }
      resetEEPROM();
      Serial.println("EEPROM RESET SUCCESS!!");
      delay(1000);
      for (int i = 0; i < sizeof(clear) - 1; i++)
      {
        char c = pgm_read_byte(&clear[i]);
        Serial.print(c);
      }
    }
    // dyhs 입력하여 로직 실행
    else if (input == "dyhs")
    {
      for (int i = 0; i < 3; i++)
      {
        Serial.println();
      }
      for (int i = 0; i < sizeof(intro) - 1; i++)
      {
        char c = pgm_read_byte(&intro[i]);
        Serial.print(c);
      }
    }
    // 메뉴 선택
    else if (input == "help")
    {
      for (int i = 0; i < 3; i++)
      {
        Serial.println();
      }
      for (int i = 0; i < sizeof(gameRule) - 1; i++)
      {
        char c = pgm_read_byte(&gameRule[i]);
        Serial.print(c);
      }
    }
    else if (input == "1")
    {
      for (int i = 0; i < 3; i++)
      {
        Serial.println();
      }
      for (int i = 0; i < sizeof(p1) - 1; i++)
      {
        char c = pgm_read_byte(&p1[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 10; i++)
      {
        Serial.println();
      }
      while (1)
      {
        String answer = "";
        answer = Serial.readStringUntil('\n');
        answer.trim();

        if (!answer.equals(""))
        {

          if (answer.equals("DYHS{D0_Y0u_Kn0W_Wh@T_3nC0dInG_1s?}"))
          {
            for (int i = 0; i < 3; i++)
            {
              digitalWrite(LED_PIN_1, HIGH);
              delay(50);
              digitalWrite(LED_PIN_1, LOW);
              delay(50);
              digitalWrite(LED_PIN_1, HIGH);
              delay(50);
            }
            EEPROM.update(eepromAddresses[0], 1);
            Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) + "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            for (int i = 0; i < 18; i++)
            {
              Serial.println();
            }
            delay(1000);
            if (sumEEPROM() == 4)
            {
              for (int i = 0; i < sizeof(allSolve) - 1; i++)
              {
                char c = pgm_read_byte(&allSolve[i]);
                Serial.print(c);
              }
              for (int i = 0; i < 3; i++)
              {
                Serial.println();
              }
            }
            break;
          }
          else if (answer.equals("exit"))
          {
            Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            delay(1500);
            for (int i = 0; i < sizeof(clear) - 1; i++)
            {
              char c = pgm_read_byte(&clear[i]);
              Serial.print(c);
            }
            break;
          }
          else
          {
            for (int i = 0; i < 3; i++)
            {
              digitalWrite(LED_PIN_1, HIGH);
              delay(50);
              digitalWrite(LED_PIN_1, LOW);
              delay(50);
            }
            Serial.println("입력값: " + answer);
            Serial.println("정답이 아니거나 FLAG 형식에 맞지 않습니다. 다시 시도하세요.");
          }
        }
      }
    }
    else if (input == "2")
    {
      for (int i = 0; i < 3; i++)
      {
        Serial.println();
      }
      for (int i = 0; i < sizeof(p2) - 1; i++)
      {
        char c = pgm_read_byte(&p2[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 10; i++)
      {
        Serial.println();
      }
      while (1)
      {
        String answer = "";
        answer = Serial.readStringUntil('\n');
        answer.trim();

        if (!answer.equals(""))
        {

          if (answer.equals("DYHS{CQCQCQDEMAKEMAKEAR}"))
          {
            for (int i = 0; i < 3; i++)
            {
              digitalWrite(LED_PIN_2, HIGH);
              delay(50);
              digitalWrite(LED_PIN_2, LOW);
              delay(50);
              digitalWrite(LED_PIN_2, HIGH);
              delay(50);
            }
            EEPROM.update(eepromAddresses[1], 1);
            Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) + "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            for (int i = 0; i < 18; i++)
            {
              Serial.println();
            }
            delay(1000);
            if (sumEEPROM() == 4)
            {
              for (int i = 0; i < sizeof(allSolve) - 1; i++)
              {
                char c = pgm_read_byte(&allSolve[i]);
                Serial.print(c);
              }
              for (int i = 0; i < 3; i++)
              {
                Serial.println();
              }
            }
            break;
          }
          else if (answer.equals("exit"))
          {
            Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            delay(1500);
            for (int i = 0; i < sizeof(clear) - 1; i++)
            {
              char c = pgm_read_byte(&clear[i]);
              Serial.print(c);
            }
            break;
          }
          else
          {
            for (int i = 0; i < 3; i++)
            {
              digitalWrite(LED_PIN_2, HIGH);
              delay(50);
              digitalWrite(LED_PIN_2, LOW);
              delay(50);
            }
            Serial.println("입력값: " + answer);
            Serial.println("정답이 아니거나 FLAG 형식에 맞지 않습니다. 다시 시도하세요.");
          }
        }
      }
    }
    else if (input == "3")
    {
      for (int i = 0; i < 3; i++)
      {
        Serial.println();
      }
      for (int i = 0; i < sizeof(p3) - 1; i++)
      {
        char c = pgm_read_byte(&p3[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 10; i++)
      {
        Serial.println();
      }
      while (1)
      {
        String answer = "";
        answer = Serial.readStringUntil('\n');
        answer.trim();

        if (!answer.equals(""))
        {

          if (answer.equals("DYHS{0xdeadbeef}"))
          {
            for (int i = 0; i < 3; i++)
            {
              digitalWrite(LED_PIN_3, HIGH);
              delay(50);
              digitalWrite(LED_PIN_3, LOW);
              delay(50);
              digitalWrite(LED_PIN_3, HIGH);
              delay(50);
            }
            EEPROM.update(eepromAddresses[2], 1);
            Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) + "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            for (int i = 0; i < 18; i++)
            {
              Serial.println();
            }
            delay(1000);
            if (sumEEPROM() == 4)
            {
              for (int i = 0; i < sizeof(allSolve) - 1; i++)
              {
                char c = pgm_read_byte(&allSolve[i]);
                Serial.print(c);
              }
              for (int i = 0; i < 3; i++)
              {
                Serial.println();
              }
            }
            break;
          }
          else if (answer.equals("exit"))
          {
            Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            delay(1500);
            for (int i = 0; i < sizeof(clear) - 1; i++)
            {
              char c = pgm_read_byte(&clear[i]);
              Serial.print(c);
            }
            break;
          }
          else
          {
            for (int i = 0; i < 3; i++)
            {
              digitalWrite(LED_PIN_3, HIGH);
              delay(50);
              digitalWrite(LED_PIN_3, LOW);
              delay(50);
            }
            Serial.println("입력값: " + answer);
            Serial.println("정답이 아니거나 FLAG 형식에 맞지 않습니다. 다시 시도하세요.");
          }
        }
      }
    }
    else if (input == "4")
    {
      for (int i = 0; i < 3; i++)
      {
        Serial.println();
      }
      for (int i = 0; i < sizeof(p4) - 1; i++)
      {
        char c = pgm_read_byte(&p4[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 10; i++)
      {
        Serial.println();
      }
      while (1)
      {
        String answer = "";
        answer = Serial.readStringUntil('\n');
        answer.trim();

        if (!answer.equals(""))
        {

          if (answer.equals("DYHS{C0ngr@tU1AtI0nS_Y0u_h@cK3D_@11_Th3s3_d3vIc3s}"))
          {
            for (int i = 0; i < 3; i++)
            {
              digitalWrite(LED_PIN_4, HIGH);
              delay(50);
              digitalWrite(LED_PIN_4, LOW);
              delay(50);
              digitalWrite(LED_PIN_4, HIGH);
              delay(50);
            }
            EEPROM.update(eepromAddresses[3], 1);
            Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) + "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            for (int i = 0; i < 18; i++)
            {
              Serial.println();
            }
            delay(1000);
            if (sumEEPROM() == 4)
            {
              for (int i = 0; i < sizeof(allSolve) - 1; i++)
              {
                char c = pgm_read_byte(&allSolve[i]);
                Serial.print(c);
              }
              for (int i = 0; i < 3; i++)
              {
                Serial.println();
              }
            }
            break;
          }
          else if (answer.equals("exit"))
          {
            Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            delay(1500);
            for (int i = 0; i < sizeof(clear) - 1; i++)
            {
              char c = pgm_read_byte(&clear[i]);
              Serial.print(c);
            }
            break;
          }
          else
          {
            for (int i = 0; i < 3; i++)
            {
              digitalWrite(LED_PIN_4, HIGH);
              delay(50);
              digitalWrite(LED_PIN_4, LOW);
              delay(50);
            }
            Serial.println("입력값: " + answer);
            Serial.println("정답이 아니거나 FLAG 형식에 맞지 않습니다. 다시 시도하세요.");
          }
        }
      }
    }
    else if (input == "clear")
    {
      for (int i = 0; i < sizeof(clear) - 1; i++)
      {
        char c = pgm_read_byte(&clear[i]);
        Serial.print(c);
      }
    }
    else
    {
      for (int i = 0; i < 3; i++)
      {
        Serial.println();
      }
      Serial.println("input: " + input);
      Serial.println("값이 올바르지 않습니다. 다른 값을 넣어주세요.");
      for (int i = 0; i < 18; i++)
      {
        Serial.println();
      }
    }
  }
}