# WinAPI를 이용한 2D게임 제작

## 게임 소개
- 제목
하늘에서 마리오가 내려와
- 컨셉
제한된 공간에서 적을 피하며 처치. 더 많은 적을 처치한 플레이어가 승리
- 게임 종류
2인용 캐주얼 플랫폼 게임(합 앤 밤) – 버블버블, 슈퍼마리오 참고
- 패배 조건
적과 충돌
- 재미 요소 
적이 비정기적으로 점프를 하도록 하여 난이도와 스릴 UP

## 구현 내용
- 충돌 시스템 - 플랫폼과 게임캐릭터간의 충돌
- 중력 - 공중에 있을 시 아래로 추락, 점프 시 포물선 운동
- 소리 - Fmod 라이브러리 이용. 배경음악 및 효과음
- 스프라이트 - 게임캐릭터들의 상태에 따라 스프라이트 바뀜
- FSM - Move, Stand, Attack, Dead
- UI - 이벤트에 따라 SCENE 전환
- 글꼴 - AddFontResource() 사용하여 기본 글꼴 바꿈

## 클래스 구성
### 전체적 흐름
![클래스구성](./img/%ED%81%B4%EB%9E%98%EC%8A%A4%EA%B5%AC%EC%84%B1.png)

- sample - 메인 함수(Init - Frame - Render -Release)
- Clientsample - 채팅 서버 담당
- GameScene - 게임 씬 담당
