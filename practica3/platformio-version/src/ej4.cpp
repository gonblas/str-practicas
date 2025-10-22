#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
void TaskPrint(void *pvParameters);

SemaphoreHandle_t sems[3];
SemaphoreHandle_t seqMutex;

enum SequenceMode { SEQ_A = 0, SEQ_B = 1, SEQ_C = 2 };
volatile SequenceMode sequenceMode;
size_t stepIndex;

static const uint8_t seqA[] = {0, 2, 1};
static const uint8_t seqB[] = {1, 1, 2, 0};
static const uint8_t seqC[] = {2, 2, 2, 0, 1};

static const uint8_t *getSeq(SequenceMode m) {
  switch (m) {
    case SEQ_A: return seqA;
    case SEQ_B: return seqB;
    default:    return seqC;
  }
}

static size_t getSeqLen(SequenceMode m) {
  switch (m) {
    case SEQ_A: return sizeof(seqA) / sizeof(seqA[0]);
    case SEQ_B: return sizeof(seqB) / sizeof(seqB[0]);
    default:    return sizeof(seqC) / sizeof(seqC[0]);
  }
}

static SequenceMode nextSequence(SequenceMode m) {
  return (SequenceMode)((m + 1) % 3);
}

const TickType_t d = pdMS_TO_TICKS(500);

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < 3; ++i) {
    sems[i] = xSemaphoreCreateBinary();
  }

  seqMutex = xSemaphoreCreateMutex();

  sequenceMode = SEQ_A;
  stepIndex = 0;

  Serial.println("-------Secuencia A-------");
  xSemaphoreGive(sems[ seqA[0] ] );

  xTaskCreate(TaskPrint, "Tarea 1", 128, (void *)(intptr_t)0, 1, NULL);
  xTaskCreate(TaskPrint, "Tarea 2", 128, (void *)(intptr_t)1, 1, NULL);
  xTaskCreate(TaskPrint, "Tarea 3", 128, (void *)(intptr_t)2, 1, NULL);

  vTaskStartScheduler();
}

void loop() {}

void TaskPrint(void *pvParameters)
{
  const int id = (int)(intptr_t)pvParameters;
  const char *names[3] = {"Tarea 1", "Tarea 2", "Tarea 3"};

  for (;;)
  {
    xSemaphoreTake(sems[id], portMAX_DELAY);
    Serial.println(String("Tarea ") + String(id + 1));

    xSemaphoreTake(seqMutex, portMAX_DELAY);
    SequenceMode curMode = sequenceMode;
    const uint8_t *curSeq = getSeq(curMode);
    size_t curLen = getSeqLen(curMode);

    size_t nextIndex = (stepIndex + 1) % curLen;
    int nextTask = -1;

    if (nextIndex != 0) {
      nextTask = curSeq[nextIndex];
      stepIndex = nextIndex;
    } else {
      SequenceMode newMode = nextSequence(curMode);
      const uint8_t *newSeq = getSeq(newMode);
      nextTask = newSeq[0];
      sequenceMode = newMode;
      stepIndex = 0;
      switch (newMode) {
        case SEQ_A: Serial.println("-------Secuencia A-------"); break;
        case SEQ_B: Serial.println("-------Secuencia B-------"); break;
        case SEQ_C: Serial.println("-------Secuencia C-------"); break;
      }
    }

    xSemaphoreGive(seqMutex);

    vTaskDelay(d);

    if (nextTask >= 0) {
      xSemaphoreGive(sems[nextTask]);
    }
  }
}