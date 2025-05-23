#include <EEPROM.h>

// 핀 및 상수 정의
#define LED_PIN_1 9
#define LED_PIN_2 8
#define LED_PIN_3 7
#define LED_PIN_4 6
#define START_STR "START_GAME"
#define NUM_PROBLEMS 4
#define LINE_SPACING 2
#define LONG_SPACING 13
#define VERY_LONG_SPACING 21

// 문제별 정답 (쉽게 변경 가능)
const char *ANSWERS[NUM_PROBLEMS] = {"FLAG{1}", "FLAG{2}", "FLAG{3}", "FLAG{4}"};

// 각 문제에 해당하는 LED 핀
const int LED_PINS[NUM_PROBLEMS] = {LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_4};

// EEPROM 주소 정의
const int eepromAddresses[NUM_PROBLEMS] = {0, 1, 2, 3};

// 대용량 문자열(출력용 아스키아트)을 프로그램 메모리에 저장
const char intro[] PROGMEM;
const char p1[] PROGMEM;
const char p2[] PROGMEM;
const char p3[] PROGMEM;
const char p4[] PROGMEM;
const char allSolve[] PROGMEM;

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
                     "/4\n\'START_GAME\'을 입력해서 처음으로 돌아가주세요.");
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
      Serial.println("\n게임에서 나가기를 선택했습니다. \'START_GAME\'를 입력해서 처음으로 돌아가주세요.");
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