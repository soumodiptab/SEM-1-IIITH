#include "headers.h"
void *routine(void *)
{
    cout << "Hello this is thread1" << endl;
}
int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}