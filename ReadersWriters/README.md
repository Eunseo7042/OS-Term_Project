# 개요
ReaderWriter 문제는 여러 Reader와 Writer가 하나의 공유 데이터에 접근할 때 발생하는 대표적인 동기화 문제이다.
Reader는 데이터를 읽으므로 여러 Reader가 동시에 접근할 수 있지만, Writer는 데이터를 수정하기 때문에 반드시 한번에 하나만 접근할 수 있다.

Reader Preference 방식을 사용하면, Reader에게 우선권을 부여하여 여러 Reader가 동시에 공유 데이터를 읽을 수 있다. 
Writer Preference 방식을 사용하면, Writer가 접근을 요청한 동안 새로운 Reader의 접근을 차단하여 Writer가 무한정 대기하는
Writer starvation 문제를 방지할 수 있다. 

# 구현 방법 및 결과
- pthread
- semaphore

[Reader]
Reader가 하나라도 존재하는 동안 Writer의 접근을 제한한다. 
sem_wait(&rmutex); 
read_count++; 
if(read_count == 1) 
  sem_wait(&resource); 
sem_post(&rmutex); 
<img width="1021" height="677" alt="image" src="https://github.com/user-attachments/assets/e297cf0a-aa99-4d9a-80dd-0909ce7ad8d7" />


[Writer]
Writer가 대기하는 동안 새로운 Reader가 들어오지 못한다. 
sem_wait(&wmutex); 
write_count++; 
if(write_count == 1) 
  sem_wait(&readTry); 
sem_post(&wmutex);
<img width="587" height="488" alt="image" src="https://github.com/user-attachments/assets/711b7008-bbf7-425d-93ab-2d4add2dcbad" />

# 평가
Reader preference를 통해 여러 Reader가 동시에 접근 가능하여 처리 성능이 높아진다.
하지만, Writer starvation이 발생할 수 있다. 
Writer preference를 통해 Writer의 starvation을 방지하고, 데이터 일관성을 유지했다. 데이터의 일관성을 유지할 수 있어 공유 자원에 대해서도 안전한 접근이 가능하다.
하지만, Reader의 대기시간이 증가할 수 있고, 처리량 또한 감소할 수 있다. 

# 결론 및 느낀 점
Reader에게 우선권이 부여되면 Writer Starvation이 발생할 수 있고, 이를 해결하기 위해 writer가 대기하는 동안 새로운 Reader의 접근을 막으면 된다고 이론으로 알고있었지만 실제로 실습해보니 해당 개념이 더 쉽게 다가오는 것 같다. Reader의 성능을 높이면 곧 Writer의 성능이 떨어지고 반대의 경우에도 마찬가지이기 때문에 필요에 따라 잘 조절해야 할 것 같다. 
