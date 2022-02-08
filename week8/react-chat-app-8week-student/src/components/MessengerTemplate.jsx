import React, { useState } from "react";
import styled from "styled-components";
import TextField from "@material-ui/core/TextField";

// Sending Message 부분
function MessenagerTemplate({getChatLog}) {
  const [ MsgState, setMsgState ] = useState({ message: "", username: ""})
 
  const onMsgChange = (e) => {
		setMsgState({ ...MsgState, [e.target.name]: e.target.value })
	}

  // 메시지 입력 창에서 빈 경우에는 ‘메시지를 입력하세요‘라는 내용의 경고 창 출력 후 리턴(alert 함수 사용)
  // 사용자의 이름 입력 창이 빈 경우에는 사용자 이름을 ‘이름없음’으로 저장
  // MsgState의 속성(키)들의 값을 빈 문자열로 초기화
	const onMsgSubmit = (e) => {
    e.preventDefault();
    // 8주차 실습 구현
    e=MsgState;
    if(!e.message){
      alert("메시지를 입력하세요");
      return;
    }
    else if(!e.username){
      e.username="이름없음";
    }
    getChatLog(e.username, e.message);
    // MsgState.message="";
    // MsgState.username="";
    setMsgState({ ...MsgState, username: '', message: '' });
	}

  return (
      <Form onSubmit={onMsgSubmit}>
				<Title>Sending Message</Title>
        <UserName>
          <TextField name="username" label="User Name" onChange={onMsgChange} value={MsgState.username}></TextField>
        </UserName>
        <MessageContents>
          <TextField name="message" label="Message" variant="outlined" onChange={onMsgChange} value={MsgState.message}></TextField>
        </MessageContents>
       <Button>Send</Button>
			</Form>
  );
}

// Sending Message 글씨 박스
const Title = styled.h1`
  margin: 10px;
  padding: 10px;
  // 해당 영역 모서리를 둥글게
  // 해당 영역의 배경색 변경
  // 해당 영역 안 텍스트 폰트색 변경
  // 8주차 실습 구현
  border-radius: 5px;
  background-color: #87bdd8;
  color: white;
`;

// 채팅 메시지 입력 form
const Form = styled.form`
  width: 500px;
  margin: 10px;
  padding: 20px;
  // 해당 영역 모서리를 둥글게
  // 해당 영역 모서리에 그림자
  // 해당 영역의 배경색 변경
  // 8주차 실습 구현
  border-radius: 3px;
  box-shadow: 3px 3px 3px silver, -3px -3px 3px silver;
  background-color: #cfe0e8;
`;

// username 표시
const UserName = styled.div`
  margin: 40px;
`;

// 채팅 메시지 부분
const MessageContents = styled.div`
  margin: 30px;
`;

// send 버튼
const Button = styled.button`
  margin-top: 60px;
  padding: 10px;
  // 해당 영역 모서리를 둥글게
  // 해당 영역 모서리색 변경
  // 해당 영역의 배경색 변경
  // 8주차 실습 구현
  border-radius: 10px;
  border-color: silver;
  background-color: white;
`;

export default MessenagerTemplate;