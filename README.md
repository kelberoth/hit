ls -al 
mkdir 파일이름  
cd 파일이름
touch 파일이름 (폴더 안에 만들어짐)  
cd .. (폴더에서 빠져나올 떄) 
rm -rf 폴더이름 (안물어보고 삭제 함) 

A(메인코드관리자) git add, git commit, git push 
B(로그인화면) git add, git commit, git push, git pull request 

git init -깃허브 성격부여 
git remote add origin https://github.com/kelberoth/hit.git

git add . (폴더의 파일들이 업로드 할 준비)
git commit -m '처음 코드 저장소' (올릴 때 어떤메세지로 올릴 지)
git push origin master (깃허브에 보내기)
