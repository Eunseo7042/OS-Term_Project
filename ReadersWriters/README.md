# 개요
ReaderWriter 문제는 여러 Reader와 Writer가 하나의 공유 데이터에 접근할 때 발생하는 대표적인 동기화 문제이다.
Reader는 데이터를 읽으므로 여러 Reader가 동시에 접근할 수 있지만, Writer는 데이터를 수정하기 때문에 반드시 한번에 하나만 접근할 수 있다.

Writer Preference 방식을 사용하면, Writer가 접근을 요청한 동안 새로운 Reader의 접근을 차단하여 Writer가 무한정 대기하는
Writer starvation 문제를 방지할 수 있다. 
