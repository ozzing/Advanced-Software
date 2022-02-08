import React from "react";
import styled from "styled-components";

import ChatLogItem from "./ChatLogItem";


function ChatLogTemplate({chats}) {
  // chats 배열을 받아 저장해 둔 채팅 로그를 보여줌
  // ChatLogItem 컴포넌트 사용

  return (
    <ChatContainer>
      <h1>Chat Log</h1>
      {/* 8주차 실습 구현 */
      chats.map((item) => {
        return <ChatLogItem chat={item}/>
        //alert(JSON.stringify(item))
      })
      }
    </ChatContainer>
  );

}

const ChatContainer = styled.div`  
  width: 500px;
  margin: 10px;
  padding: 20px;
  // 해당 영역 모서리를 둥글게
  // 해당 영역 모서리에 그림자
  // 해당 영역의 배경색 변경
  // 8주차 실습 구현
  border-radius: 10px;
  box-shadow: 3px 3px 3px silver, -3px -3px 3px silver;
  background-color: #b7d7e8;
`;

export default ChatLogTemplate;