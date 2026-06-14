# 개요
Dining Philosophers 문제는 운영체제에서 교착상태(Deadlock)을 설명하기 위한 대표적인 동기화 문제이다. 
5명의 철학자가 원형 테이블에 앉아 식사를 위해 자신의 왼쪽과 오른쪽 포크를 모두 획득하려 할 때 Deadlock이 발생할 수 있다. 

# 구현 방법
- pthread
- mutex

[requesting_all_resources]
pthread_mutex_lock(&table_lock); 
pthread_mutex_lock(&forks[id]); 
pthread_mutex_lock(&forks[(id+1)%N]); 
pthread_mutex_unlock(&table_lock);
<img width="785" height="647" alt="image" src="https://github.com/user-attachments/assets/c709ce39-7782-4ca4-9b5b-f61041f13c41" />
