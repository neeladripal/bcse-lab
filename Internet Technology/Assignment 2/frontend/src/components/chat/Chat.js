import React from "react";
import ProfileHeader from "../common/ProfileHeader";
import Messages from "./Messages";
import ChatBox from "./ChatBox";

function Chat(props) {
  const { selectedChat, self, onMessageSend } = props;

  const privateChatToProfileHeader = (chat) => {
    return {
      avatar: chat.users[0].profilePic,
      name: chat.users[0].name,
    };
  };

  const globalChatToProfileHeader = () => {
    return {
      avatar: process.env.PUBLIC_URL + "global.png",
      name: "Global",
    };
  };

  return (
    <div className="chat">
      <ProfileHeader
        chat={
          selectedChat.type === "private"
            ? privateChatToProfileHeader(selectedChat)
            : globalChatToProfileHeader()
        }
      />
      <Messages
        chatType={selectedChat.type}
        messageList={selectedChat.messages}
        selfId={self._id}
      />
      <ChatBox key={selectedChat._id} onMessageSend={onMessageSend} />
    </div>
  );
}

export default Chat;
