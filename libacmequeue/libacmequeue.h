#define QUEUE_PATH "/tmp"

class AcmeQueue {
  private:
    char dirName[255];
    char* queueName;
    char* queuePath;
  public:
    AcmeQueue(const char *qn); 
    AcmeQueue(const char *qp, const char *qn);
    int Push(const char *s);
    bool Pop(char *s);
};
