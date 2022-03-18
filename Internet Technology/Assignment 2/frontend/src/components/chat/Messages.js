import React, { createRef, useEffect } from "react";
import moment from "moment";

function Message(props) {
  const { chatType, message, selfId } = props;
  const { sender, type, content, addedOn } = message;

  const getSenderText = (chatType, senderName) => {
    if (chatType !== "private")
      return <div className="sender">{senderName}</div>;
    else return "";
  };

  return (
    <div
      style={{
        "--justify-content": `${
          sender._id === selfId ? "flex-end" : "flex-start"
        }`,
      }}
      className="message-wrapper"
    >
      <div
        style={{
          "--background": `${sender._id === selfId ? "#daf8cb" : "white"}`,
        }}
        className="message-content"
      >
        {sender._id !== selfId && getSenderText(chatType, sender.name)}
        {type === "text" ? (
          <span className="message-text">{content}</span>
        ) : (
          <img className="message-img" src={content} alt="" />
        )}
        <div className="message-time">{moment(addedOn).calendar()}</div>
      </div>
    </div>
  );
}

function Messages(props) {
  const { chatType, messageList, selfId } = props;
  const messagesEnd = createRef();

  const scrollToBottom = () => {
    messagesEnd.current.scrollIntoView({ behavior: "smooth" });
  };

  useEffect(() => scrollToBottom());
  return (
    <div className="message-area">
      {messageList.map((message) => (
        <Message
          key={message._id}
          chatType={chatType}
          message={message}
          selfId={selfId}
        />
      ))}
      <div style={{ float: "left", clear: "both" }} ref={messagesEnd}></div>
    </div>
  );
}

export default Messages;
