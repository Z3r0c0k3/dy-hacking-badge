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
"                                       문제 1 : 안전한 비밀번호는 무엇일까요?\n"
"                                       문제 2 : 어떤 와이파이가 안전할까요?\n"
"                                       문제 3 : 안전한 다운로드\n"
"                                       문제 4 : 공개 게시판에 글올리기\n"
"                                       clear : 시리얼 모니터의 모든 내용이 사라집니다.\n"
"                                       help  : 게임 진행방법에 대한 설명이 들어있습니다.\n"                                    
"====================================================================================================================\n";

const char gameRule[] PROGMEM = 
" ---------------------------------------------------<< 게임 방법 >>---------------------------------------------------\n"
"                               1. 풀고싶은 문제의 번호를 입력해주세요!\n"
"                               2. 출제된 문제의 답을 찾아서 정답을 입력해주세요!\n"
"                               3. 정답을 맞춘다면 번호에 맞는 LED에 불이 켜져요!\n"
"                               4. 문제에 들어가서 나오고 싶다면 \'exit\'를 입력해주세요!\n"
"====================================================================================================================\n"
"\n"
"# #   ###  ##   #       ### ###    #     #### ### ##  ### ##  ##  ####   ##### ### ###   ## #####           ##   # #\n"
"# #    ##  ##   #        ##  #    ###   ##  #  ## #    ##  ## #  ##  #   ### #  ##  ### ###  ##             ##   # #\n"
"       ## #### #  ###    #####   #  ##  ##     ###     ##  ####  ##       ##    ##  # ## ##  ####    ## #   #\n"
"       ##  ##     ##     ##  #   #####  ##     ####    ##  ####  ## ##    ##    ##  # ## ##  ##     # ##\n"
"       ##  ##      ##    ##  #   #  ##  ##  #  ## ##   ##  # ##  ##  #    ##    ##  # ## ##  ## #           #\n"
"      ###   ##    ###   ### ### ##  ###  ###  ### ### ### ##  #   ####   ####  ### ##  # ## #####           #\n"
"\n"
"                                     \" 지금 당장 HACKING BADGE SOLVER에 도전하세요! \"\n"
"                                         (\'dyhs\'를 입력하여 처음으로 돌아가세요.)\n"
"====================================================================================================================\n";

const char p1[] PROGMEM = 
"====================================================================================================================\n"
" --------------------------- -------------<  문제 01. 안전한 비밀번호는 무엇일까요?  >-------------------------------------- \n"
"|                                                                                                                  |\n"
"|                                     아래 비밀번호 중에서 가장 안전한 비밀번호는 무엇일까요?                                    |\n"
"|                                                                                                                  |\n"
" ---------------------------------------------<  알맞는 숫자를 입력해주세요  >-------------------------------------------- \n"
"|                                            1. 1234           2. password                                         |\n"
"|                                            3. qwerty1234     4. H!3l*09pQ                                        |\n"
" ------------------------------------------------------------------------------------------------------------------ \n"
"====================================================================================================================\n";

const char p2[] PROGMEM = 
"====================================================================================================================\n"
" -----------------------------------------<  문제 02. 어떤 와이파이가 안전할까요?  >--------------------------------------- \n"
"|                                                                                                                  |\n"
"|                                     아래 와이파이 중에서 가장 안전한 와이파이는 무엇일까요?                                    |\n"
"|                                                                                                                  |\n"
" ---------------------------------------------<  알맞는 숫자를 입력해주세요  >-------------------------------------------- \n"
"|                                  1. 개방형 공공 와이파이           2. 개방형 카페 와이파이                                 |\n"
"|                                  3. 비밀번호가 없는 와이파이        4. 비밀번호가 있는 집 와이파이                            |\n"
" ------------------------------------------------------------------------------------------------------------------ \n"
"====================================================================================================================\n";

const char p3[] PROGMEM = 
"====================================================================================================================\n"
" ----------------------------------------------<  문제 03. 안전한 다운로드  >------------------------------------------- \n"
"|                                                                                                                  |\n"
"|                                     게임을 다운로드하려고 할 때, 어느 사이트가 가장 안전할까요?                                |\n"
"|                                                                                                                  |\n"
" ---------------------------------------------<  알맞는 숫자를 입력해주세요  >-------------------------------------------- \n"
"|                                 1. 공식 게임 웹사이트         2. 친구가 보내준 다운로드 링크                                |\n"
"|                                 3. 무료 다운로드 사이트        4. 누가 보냈는지 알 수 없는 이메일에 첨부된 설치 파일              |\n"
" ------------------------------------------------------------------------------------------------------------------ \n"
"====================================================================================================================\n";

const char p4[] PROGMEM = 
"====================================================================================================================\n"
" -------------------------------------------<  문제 04. 공개 게시판에 글올리기  >----------------------------------------- \n"
"|                                                                                                                  |\n"
"|                                        온라인 공개 게시판에 어떤 정보를 올리면 안 될까요?                                    |\n"
"|                                                                                                                  |\n"
" ---------------------------------------------<  알맞는 숫자를 입력해주세요  >-------------------------------------------- \n"
"|                                     1. 오늘 나의 기분           2. 내가 간 카페의 주소                                   |\n"
"|                                     3. 친구의 전화번호           4. 좋아하는 게임의 이름                                  |\n"
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

void resetEEPROM() {
    for (int i = 0; i < 4; i++) {
        EEPROM.update(eepromAddresses[i], 0);  // 모든 LED 상태를 끈 상태(0)로 초기화
    }
}

int statusEEPROM(int idx) {
  if (EEPROM.read(eepromAddresses[idx]) == 1) {
    return 1;
  }
  else {
    return 0;
  }
}

int sumEEPROM() {
  int res = 0;
  for (int i=0; i<4; i++) {
    res = res + statusEEPROM(i);
  }
  return res;
}

void setup() {
  Serial.begin(4800);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  
  //resetEEPROM();
  
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

void loop() {
  if (Serial) {
    // 입력 대기 시작
    String input = Serial.readStringUntil('\n');
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
    else if (input == "reset") {
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
      resetEEPROM();
      Serial.println("EEPROM RESET SUCCESS!!");
      delay(1000);
      for (int i = 0; i < sizeof(clear) - 1; i++) {
        char c = pgm_read_byte(&clear[i]);
        Serial.print(c);
      }
    }
    //dyhs 입력하여 로직 실행
    else if (input == "dyhs") {
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
      for (int i = 0; i < sizeof(intro) - 1; i++) {
        char c = pgm_read_byte(&intro[i]);
        Serial.print(c);
      }
    }
    // 메뉴 선택
    else if(input == "help") {
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
      for (int i = 0; i < sizeof(gameRule) - 1; i++) {
        char c = pgm_read_byte(&gameRule[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
    }
    else if(input == "1") {
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
      for (int i = 0; i < sizeof(p1) - 1; i++) {
        char c = pgm_read_byte(&p1[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 10; i++) {
        Serial.println();
      }
      while(1) {
        String answer = "";
        answer = Serial.readStringUntil('\n');
        answer.trim();
        
        if (!answer.equals("")) {

          if(answer.equals("4")) {
            for (int i=0; i<3; i++) {
              digitalWrite(LED_PIN_1, HIGH);
              delay(50);
              digitalWrite(LED_PIN_1, LOW);
              delay(50);
              digitalWrite(LED_PIN_1, HIGH);
              delay(50);
            }
            EEPROM.update(eepromAddresses[0], 1);
            Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) + "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            for (int i = 0; i < 18; i++) {
            Serial.println();
            }
            delay(1000);
            if (sumEEPROM() == 4) {
              for (int i = 0; i < sizeof(allSolve) - 1; i++) {
                char c = pgm_read_byte(&allSolve[i]);
                Serial.print(c);
              }
              for (int i = 0; i < 3; i++) {
                Serial.println();
              }
            }
            break;
          }
          else if(answer.equals("exit")) {
            Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            delay(1500);
            for (int i = 0; i < sizeof(clear) - 1; i++) {
              char c = pgm_read_byte(&clear[i]);
              Serial.print(c);
            }
            break;
          }
          else {
            for (int i=0; i<3; i++) {
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
    else if(input == "2") {
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
      for (int i = 0; i < sizeof(p2) - 1; i++) {
        char c = pgm_read_byte(&p2[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 10; i++) {
        Serial.println();
      }
      while(1) {
        String answer = "";
        answer = Serial.readStringUntil('\n');
        answer.trim();
        
        if (!answer.equals("")) {

          if(answer.equals("4")) {
            for (int i=0; i<3; i++) {
              digitalWrite(LED_PIN_2, HIGH);
              delay(50);
              digitalWrite(LED_PIN_2, LOW);
              delay(50);
              digitalWrite(LED_PIN_2, HIGH);
              delay(50);
            }
            EEPROM.update(eepromAddresses[1], 1);
            Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) + "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            for (int i = 0; i < 18; i++) {
            Serial.println();
            }
            delay(1000);
            if (sumEEPROM() == 4) {
              for (int i = 0; i < sizeof(allSolve) - 1; i++) {
                char c = pgm_read_byte(&allSolve[i]);
                Serial.print(c);
              }
              for (int i = 0; i < 3; i++) {
                Serial.println();
              }
            }
            break;
          }
          else if(answer.equals("exit")) {
            Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            delay(1500);
            for (int i = 0; i < sizeof(clear) - 1; i++) {
              char c = pgm_read_byte(&clear[i]);
              Serial.print(c);
            }
            break;
          }
          else {
            for (int i=0; i<3; i++) {
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
    else if(input == "3") {
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
      for (int i = 0; i < sizeof(p3) - 1; i++) {
        char c = pgm_read_byte(&p3[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 10; i++) {
        Serial.println();
      }
      while(1) {
        String answer = "";
        answer = Serial.readStringUntil('\n');
        answer.trim();
        
        if (!answer.equals("")) {

          if(answer.equals("1")) {
            for (int i=0; i<3; i++) {
              digitalWrite(LED_PIN_3, HIGH);
              delay(50);
              digitalWrite(LED_PIN_3, LOW);
              delay(50);
              digitalWrite(LED_PIN_3, HIGH);
              delay(50);
            }
            EEPROM.update(eepromAddresses[2], 1);
            Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) + "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            for (int i = 0; i < 18; i++) {
            Serial.println();
            }
            delay(1000);
            if (sumEEPROM() == 4) {
              for (int i = 0; i < sizeof(allSolve) - 1; i++) {
                char c = pgm_read_byte(&allSolve[i]);
                Serial.print(c);
              }
              for (int i = 0; i < 3; i++) {
                Serial.println();
              }
            }
            break;
          }
          else if(answer.equals("exit")) {
            Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            delay(1500);
            for (int i = 0; i < sizeof(clear) - 1; i++) {
              char c = pgm_read_byte(&clear[i]);
              Serial.print(c);
            }
            break;
          }
          else {
            for (int i=0; i<3; i++) {
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
    else if(input == "4") {
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
      for (int i = 0; i < sizeof(p4) - 1; i++) {
        char c = pgm_read_byte(&p4[i]);
        Serial.print(c);
      }
      for (int i = 0; i < 10; i++) {
        Serial.println();
      }
      while(1) {
        String answer = "";
        answer = Serial.readStringUntil('\n');
        answer.trim();
        
        if (!answer.equals("")) {

          if(answer.equals("3")) {
            for (int i=0; i<3; i++) {
              digitalWrite(LED_PIN_4, HIGH);
              delay(50);
              digitalWrite(LED_PIN_4, LOW);
              delay(50);
              digitalWrite(LED_PIN_4, HIGH);
              delay(50);
            }
            EEPROM.update(eepromAddresses[3], 1);
            Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) + "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            for (int i = 0; i < 18; i++) {
            Serial.println();
            }
            delay(1000);
            if (sumEEPROM() == 4) {
              for (int i = 0; i < sizeof(allSolve) - 1; i++) {
                char c = pgm_read_byte(&allSolve[i]);
                Serial.print(c);
              }
              for (int i = 0; i < 3; i++) {
                Serial.println();
              }
            }
            break;
          }
          else if(answer.equals("exit")) {
            Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
            delay(1500);
            for (int i = 0; i < sizeof(clear) - 1; i++) {
              char c = pgm_read_byte(&clear[i]);
              Serial.print(c);
            }
            break;
          }
          else {
            for (int i=0; i<3; i++) {
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
    else if(input == "clear") {
      for (int i = 0; i < sizeof(clear) - 1; i++) {
      char c = pgm_read_byte(&clear[i]);
      Serial.print(c);
      }
    }
    else {
      for (int i = 0; i < 3; i++) {
        Serial.println();
      }
      Serial.println("input: "+input);
      Serial.println("값이 올바르지 않습니다. 다른 값을 넣어주세요.");
      for (int i = 0; i < 18; i++) {
        Serial.println();
      }
    }
  }
}