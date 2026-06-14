# 개요
Dining Philosophers 문제는 운영체제에서 교착상태(Deadlock)을 설명하기 위한 대표적인 동기화 문제이다. 
5명의 철학자가 원형 테이블에 앉아 식사를 위해 자신의 왼쪽과 오른쪽 포크를 모두 획득하려 할 때 Deadlock이 발생할 수 있다. 

# 구현 방법 및 결과
- pthread
- mutex

[requesting_all_resources]
철학자가 식사를 하기 전 양쪽 포크를 모두 확보한 후 식사한다. 
pthread_mutex_lock(&table_lock); 

pthread_mutex_lock(&forks[id]); 
pthread_mutex_lock(&forks[(id+1)%N]); 

pthread_mutex_unlock(&table_lock);
<img width="785" height="647" alt="image" src="https://github.com/user-attachments/assets/c709ce39-7782-4ca4-9b5b-f61041f13c41" />

[resource_ordering]
각 철학자는 번호가 작은 포크를 먼저 획드가고, 번호가 큰 포크를 나중에 획득한다.
int first = left < right ? left : right; 
int second = left < right ? right : left;

pthread_mutex_lock(&forks[first]); 
pthread_mutex_lock(&forks[second]);

pthread_mutex_unlock(&forks[second]); 
pthread_mutex_unlock(&forks[first]);
<img width="926" height="672" alt="image" src="https://github.com/user-attachments/assets/89437770-caf6-4bd9-b294-18491c73cf3f" />

# 평가
자원을 모두 확보한 후 동작하는 방식을 사용하면, 구현이 단순하지만 병렬서잉 낮고, 자원을 필요로 하는 다른 이들의 대기가 발생한다.
모두 동일한 자원 규칙을 따르는 방식을 사용하면 자원활용이 효률적이고 Circular wait이 제거되어 병렬성이 높지만 구현이 복잡하다. 

# 결론 및 느낀 점
Requesting All Resources는 구현이 단순하지만 자원 획득 과정이 직렬화되어 병렬성이 낮다. 반면 Resource Ordering은 모든 철학자가 동일한 자원 획득 순서를 따르도록 하여 Circular Wait를 제거하고 Deadlock을 방지하며, 더 높은 병렬성을 제공한다. 따라서 자원 활용 측면에서는 Resource Ordering 방식이 더 효율적이다.
식사하는 철학자 문제를 처음 만났을 땐, 한 사람이 양쪽 포크를 모두 사용하고, 그 옆의 사람들은 좀 기다리면 되지 않나 싶었는데, 자원 획득 순서를 통일하여 서로 포크가 겹치지 않게 하는 방법이 더 효율적이라는 것을 깨닫게 되었다. 어떤 문제를 마주했을 때 해결하려고 하는 것이 좋지만, 해결하려는 생각이 너무 앞서면 비효율적인 방법으로 해결하게 될 수 있다 느꼈다. 
