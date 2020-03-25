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
  - 각 클래스들은 Init에서 필요한 정보 생성 및 로드, 할당
  - Frame에서 필요한 계산
  - Render를 통해 화면에 뿌려진다. 
  - 모든 작업이 완료된 뒤에는 Release를 통해 할당 해제한다.
- Clientsample - 채팅 클라이언트 담당
- GameScene - 게임 씬 담당

#### sylib
1. sywindow, sycore 클래스
![windows -core](./img/corewindow.png)
 - syWindow
  - 윈도우를 생성한다
  - 윈도우 인스턴스 핸들, 윈도우 핸들, Client 크기 
- syCore
  - 게임의 기본 흐름을 관장하는 core를 생성한다.

2. 클래스 매니저들
![클래스매니저](./img/클래스매니저.png)
- Singleton Pattern 사용
  - 전담 매니저 사용
  - 리소스를 전담 매니저 통해 불러 코드 어디서든 사용 가능하게
  - 리소스 중복 호출을 방지
+ syInput : 마우스, 키보드 등 유저 입력 관리
+ syBitmapMgr : 비트맵 파일 리소스 관리
+ syFSM 
+ syScriptManager : 필요한 리소스 스크립트화 하여 관리
+ sySoundMgr

3. UI
 ![UI](./img/UI.png)
 ![scene](./img/scene.png)
 - 실행시 LoginScene(서버 연결) - Lobby Scene(게임시작준비/결과) - InGameScene(게임진행) 
 - 게임오버될경우 Lobby Scene으로 돌아감\
 
 
 4. 오브젝트
 ![Object](./img/오브젝트.png)
- syCharacter
   - sprite클래스 상속
   - 비트맵 크기 조절, 중력, 발판과의 충돌 처리 구현
- syPlayer
  - 프레임마다 방향키 입력시 이동 구현
syEnemy
  - FSM 통해 움직임 구현 및 스프라이트 변경
syBackGround
  - tiled 이용.
  - 모든 배경을 tile화 하여 각각 비트맵 그려줌
    > cpu 점유율이 너무 높아짐
    >> 충돌 체크를 해야 하는 발판들만 tile로 구현 
