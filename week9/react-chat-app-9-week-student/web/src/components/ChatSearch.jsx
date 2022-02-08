// 채팅 키워드 검색창 & 검색 버튼에 대한 컴포넌트 작성
import React, { useState } from "react";
import styled from "styled-components";
import TextField from "@material-ui/core/TextField";

// chat 객체 하나를 인자로 받아 한 줄로 표현하기 위한 컴포넌트
function ChatSearch({func}) {
    const [kwState, setKwState] = useState({ keyword: "" })

    const onKwChange = (e) => {
            setKwState({ ...kwState, [e.target.name]: e.target.value })
    }

  return (
    <div>
        <SearchContainer>
        <TextField
          name="keyword"
          value = {kwState.keyword}
          onChange={(e) => onKwChange(e)}
          id="outlined-multiline-static"
          variant="outlined"
          label="Keyword"
        />
        <Button onClick={() => {func(kwState.keyword)}}>Search</Button>
        </SearchContainer>
    </div>
  );

}

const SearchContainer = styled.div`
  width : 500px;
  margin-top: 20px;
`;

const Button = styled.button`
  margin-top: 8px;
  margin-left: 80px;
  padding: 10px;
  background-color: white;
  border-color: #c8a951;
  border-radius: 5px;
`;
export default ChatSearch;