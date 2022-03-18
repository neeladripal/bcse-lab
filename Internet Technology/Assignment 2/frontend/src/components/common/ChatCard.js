import React from "react";

function ChatCard(props) {
  const { chat, onChatSelect, _id } = props;
  const { name, avatar, lastMessage, lastMessageTime } = chat;
  return (
    <div className="chat-card" onClick={(e) => onChatSelect(_id)}>
      <img
        src={avatar || process.env.PUBLIC_URL + "avatar.png"}
        alt=""
        className="avatar"
      />
      <div className="info">
        <span className="name">{name}</span>
        <span className="last-message">{lastMessage}</span>
      </div>
      <span className="message-time">{lastMessageTime}</span>
    </div>
  );
}

export default ChatCard;
