#include <EEPROM.h>

// 핀 및 상수 정의
#define LED_PIN_1 9
#define LED_PIN_2 8
#define LED_PIN_3 7
#define LED_PIN_4 6
#define START_STR "dyhs"
#define NUM_PROBLEMS 4
#define LINE_SPACING 2
#define LONG_SPACING 13
#define VERY_LONG_SPACING 21

// 문제별 정답 (쉽게 변경 가능)
const char *ANSWERS[NUM_PROBLEMS] = {"DYHS{D0_Y0u_Kn0W_Wh@T_3nC0dInG_1s?}", "DYHS{CQCQCQDEMAKEMAKEAR}", "DYHS{0xdeadbeef}", "DYHS{C0ngr@tU1AtI0nS_Y0u_h@cK3D_@11_Th3s3_d3vIc3s}"};

// 각 문제에 해당하는 LED 핀
const int LED_PINS[NUM_PROBLEMS] = {LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_4};

// EEPROM 주소 정의
const int eepromAddresses[NUM_PROBLEMS] = {0, 1, 2, 3};

// 대용량 문자열(출력용 아스키아트)을 프로그램 메모리에 저장
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
    "                                      문제 1  :  Decoding This Word\n"
    "                                      문제 2  :  CQ CQ CQ\n"
    "                                      문제 3  :  ZOMBIE\n"
    "                                      문제 4  :  King Carsar\n"
    "                                      clear  :  시리얼 모니터의 모든 내용이 사라집니다\n"
    "                                      help   :  게임 설명과 FLAG 형식이 들어있습니다\n"
    "                                      status :  어떤 문제를 풀이했는지 보여줍니다.\n"
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
    "|                                숫자를 16진수와 변환하면 나온다고 하는데.. 어떻게 해야할까요?                                   |\n"
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

// PROGMEM에서 문제 설명 텍스트 배열 (편리한 접근을 위해)
const char *const problemTexts[NUM_PROBLEMS] PROGMEM = {p1, p2, p3, p4};

// EEPROM 초기화 함수
void resetEEPROM()
{
  for (int i = 0; i < NUM_PROBLEMS; i++)
  {
    EEPROM.update(eepromAddresses[i], 0);
  }
}

// EEPROM 특정 문제 상태 확인
int statusEEPROM(int idx)
{
  return EEPROM.read(eepromAddresses[idx]) == 1 ? 1 : 0;
}

// 모든 문제 해결 상태의 합 계산
int sumEEPROM()
{
  int sum = 0;
  for (int i = 0; i < NUM_PROBLEMS; i++)
  {
    sum += statusEEPROM(i);
  }
  return sum;
}

// 모든 문제가 해결되었는지 확인
bool allProblemsCompleted()
{
  for (int i = 0; i < NUM_PROBLEMS; i++)
  {
    if (!statusEEPROM(i))
      return false;
  }
  return true;
}

// PROGMEM에서 문자열 출력 함수
void printProgmemString(const char *progmemString)
{
  for (int i = 0; i < strlen_P(progmemString); i++)
  {
    char c = pgm_read_byte(progmemString + i);
    Serial.print(c);
  }
}

// 빈 줄 출력 함수
void printEmptyLines(int count)
{
  for (int i = 0; i < count; i++)
  {
    Serial.println();
  }
}

// LED 깜빡임 패턴 함수
void blinkLED(int pin, int times, int onTime = 50, int offTime = 50)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(pin, HIGH);
    delay(onTime);
    digitalWrite(pin, LOW);
    delay(offTime);
    digitalWrite(pin, HIGH);
    delay(onTime);
    digitalWrite(pin, LOW);
    delay(offTime);
  }
}

// LED 애니메이션 실행
void playLEDAnimation(int delayTime = 50)
{
  // 역순으로 LED 켜기
  for (int i = 9; i >= 6; i--)
  {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }
  // 순서대로 LED 켜기
  for (int i = 6; i <= 9; i++)
  {
    digitalWrite(i, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }
}

// 모든 문제가 해결되었을 때 실행
void showCompletionMessage()
{
  printProgmemString(allSolve);
  printEmptyLines(LINE_SPACING);
}

// 문제 풀이 처리 함수
void handleProblem(int problemNumber)
{
  int index = problemNumber - 1;
  int ledPin = LED_PINS[index];

  printEmptyLines(LINE_SPACING);
  printProgmemString((const char *)pgm_read_word(&problemTexts[index]));
  printEmptyLines(LONG_SPACING);

  while (true)
  {
    String answer = Serial.readStringUntil('\n');
    answer.trim();

    if (answer.equals(""))
      continue;

    if (answer.equals(ANSWERS[index]))
    {
      // 정답 처리
      blinkLED(ledPin, 3);
      EEPROM.update(eepromAddresses[index], 1);
      Serial.println("정답입니다!! 정답 갯수:" + String(sumEEPROM()) +
                     "/4\n\'dyhs\'를 입력해서 처음으로 돌아가주세요.");
      printEmptyLines(VERY_LONG_SPACING);
      delay(1000);

      if (sumEEPROM() == NUM_PROBLEMS)
      {
        showCompletionMessage();
      }
      break;
    }
    else if (answer.equals("exit"))
    {
      // 종료 처리
      Serial.println("\n게임에서 나가기를 선택했습니다. \'dyhs\'를 입력해서 처음으로 돌아가주세요.");
      delay(1500);
      printProgmemString(VERY_LONG_SPACING);
      break;
    }
    else
    {
      // 오답 처리
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(ledPin, HIGH);
        delay(50);
        digitalWrite(ledPin, LOW);
        delay(50);
      }
      Serial.println("입력값: " + answer);
      Serial.println("정답이 아니거나 FLAG 형식에 맞지 않습니다. 다시 시도하세요.");
    }
  }
}

void setup()
{
  // 시리얼 통신 시작
  Serial.begin(4800);

  // LED 핀 모드 설정
  for (int i = 0; i < NUM_PROBLEMS; i++)
  {
    pinMode(LED_PINS[i], OUTPUT);
  }

  // 시작 애니메이션
  playLEDAnimation(100);

  // 상태 표시
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_PIN_1, EEPROM.read(eepromAddresses[i]) ? HIGH : LOW);
  }
  // 시리얼 연결 시, welcome 메시지 출력
  if (Serial)
  {
    printEmptyLines(LINE_SPACING);
    Serial.println("게임을 시작합니다. \'help\'를 입력하여 도움말을 확인하세요.");
    delay(1000);
    printProgmemString(intro);
    printEmptyLines(LINE_SPACING);
    // 성공 메시지 출력
    if (allProblemsCompleted())
    {
      showCompletionMessage();
    }
  }
}

void loop()
{
  if (Serial)
  {
    // 입력 대기
    String input = Serial.readStringUntil('\n');
    input.trim();

    // 빈 입력 처리 (모든 문제 완료시 LED 애니메이션)
    if (input == "")
    {
      if (allProblemsCompleted())
      {
        playLEDAnimation();
      }
    }
    // EEPROM 초기화
    else if (input == "reset")
    {
      printEmptyLines(LINE_SPACING);
      resetEEPROM();
      Serial.println("EEPROM RESET SUCCESS!!");
      delay(1000);
      printEmptyLines(VERY_LONG_SPACING);
    }
    // 게임 시작
    else if (input == START_STR)
    {
      printEmptyLines(LINE_SPACING);
      delay(1000);
      printProgmemString(intro);
      printEmptyLines(LINE_SPACING);
    }
    // 도움말
    else if (input == "help")
    {
      printEmptyLines(LINE_SPACING);
      printProgmemString(gameRule);
      printEmptyLines(LINE_SPACING);
    }
    // 화면 지우기
    else if (input == "clear")
    {
      printEmptyLines(VERY_LONG_SPACING);
    }
    // 풀이한 문제 확인
    else if (input == "status")
    {
      printEmptyLines(LINE_SPACING);
      Serial.println("문제를 풀면 O, 풀지 않았다면 X로 표시됩니다.\n");
      Serial.println("       < 문제 풀이 상태 >     ");
      Serial.println("  +-----+-----+-----+-----+");
      Serial.println("  |  1  |  2  |  3  |  4  |");
      Serial.println("  +-----+-----+-----+-----+");
      Serial.print("  |");
      for (int i = 0; i < NUM_PROBLEMS; i++)
      {
        if (statusEEPROM(i))
        {
          Serial.print("  O  |"); // 해결된 문제는 O
        }
        else
        {
          Serial.print("  X  |"); // 미해결 문제는 X
        }
      }
      Serial.println("\n  +-----+-----+-----+-----+");

      if (allProblemsCompleted())
      {
        printEmptyLines(LINE_SPACING);
        showCompletionMessage();
      }
      else
      {
        printEmptyLines(LONG_SPACING);
      }
    }
    // 문제 선택 (1-4)
    else if (input.length() == 1 && input[0] >= '1' && input[0] <= '4')
    {
      int problemNumber = input.toInt();
      handleProblem(problemNumber);
    }
    // 유효하지 않은 입력
    else
    {
      printEmptyLines(LINE_SPACING);
      Serial.println("input: " + input);
      Serial.println("값이 올바르지 않습니다. 다른 값을 넣어주세요.");
      printEmptyLines(VERY_LONG_SPACING);
    }
  }
}