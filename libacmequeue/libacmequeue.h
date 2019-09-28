#define QUEUE_PATH "."

class AcmeQueue {
  public:
    AcmeQueue(const char *qn); 
    AcmeQueue(const char *qp, const char *qn);
    int Push(const char *s);
    bool Pop(char *s);
  private:
    char* queueName;
    char dirName[255];
    char *queuePath;
};
