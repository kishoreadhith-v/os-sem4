#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CUSTOMERS 20
#define MAX_SOFA 4
#define NO_OF_CUST 26
#define MAX_CHAIRS 3

int customers = 0;
int customers_on_sofa = 0;
int customers_standing = 0;
int customers_cutting = 0;
pthread_t cust[NO_OF_CUST];
pthread_t barb[3];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t chair_available = PTHREAD_COND_INITIALIZER;
pthread_cond_t sofa_available = PTHREAD_COND_INITIALIZER;
pthread_cond_t payment_ready = PTHREAD_COND_INITIALIZER;
pthread_cond_t customer_served = PTHREAD_COND_INITIALIZER;

void *barbershop(void *arg)
{
    int n = *(int *)arg;

    pthread_mutex_lock(&mutex);
    if (customers >= MAX_CUSTOMERS)
    {
        pthread_mutex_unlock(&mutex);
        printf("Exiting shop %d.. \n", n);
        pthread_exit(NULL);
    }
    customers++;
    if (customers <= MAX_CHAIRS)
    {
        pthread_mutex_unlock(&mutex);
    }
    else if (customers_on_sofa < MAX_SOFA)
    {
        customers_on_sofa++;
        pthread_mutex_unlock(&mutex);
        printf("Customer %d sits on the sofa.\n", n);
    }
    else
    {
        customers_standing++;
        pthread_mutex_unlock(&mutex);
        printf("Customer %d stands.\n", n);
    }

    pthread_mutex_lock(&mutex);
    while (customers_cutting >= MAX_CHAIRS)
    {
        pthread_cond_wait(&chair_available, &mutex);
    }
    customers_cutting++;
    customers--;
    pthread_mutex_unlock(&mutex);

    printf("Customer %d sits on the barber chair (Barber %d).\n", n, (n % 3) + 1);
    sleep(3); // Haircut

    pthread_mutex_lock(&mutex);
    printf("Customer %d gets a haircut (Barber %d).\n", n, (n % 3) + 1);
    pthread_cond_signal(&customer_served);
    pthread_cond_wait(&payment_ready, &mutex);
    printf("Customer %d pays (Barber %d).\n", n, (n % 3) + 1);
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    customers_cutting--;
    pthread_cond_signal(&chair_available); // Signal availability of chair

    if (customers_standing > 0 && customers_on_sofa < MAX_SOFA)
    {
        customers_standing--;
        customers_on_sofa++;
        printf("Customer from standing moves to the sofa.\n");
        pthread_cond_signal(&sofa_available);
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *cutting(void *arg)
{
    int n = *(int *)arg;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&customer_served, &mutex);
        pthread_cond_signal(&payment_ready);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    int i, cust_id[NO_OF_CUST];

    for (i = 0; i < NO_OF_CUST; i++)
    {
        cust_id[i] = i + 1;
        pthread_create(&cust[i], NULL, barbershop, &cust_id[i]);
    }

    for (i = 0; i < 3; i++)
    {
        pthread_create(&barb[i], NULL, cutting, &cust_id[i]);
    }

    printf("Thread creation successful\n");

    for (i = 0; i < NO_OF_CUST; i++)
    {
        pthread_join(cust[i], NULL);
    }

    printf("Thread joining successful\n");
    printf("\nSimulation Ended!\n");

    return 0;
}
