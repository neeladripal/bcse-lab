import React from "react";
import moment from "moment";
import ChatCard from "../common/ChatCard";

function ChatList(props) {
  const { onChatSelect, chats, self } = props;

  const privateChatToCard = (chat, self) => {
    const { users, messages } = chat;
    let contact = { lastMessage: "", lastMessageTime: "" };
    contact.avatar = users[0].profilePic;
    contact.name = users[0].name;
    if (messages.length > 0) {
      const lastMessage = messages[messages.length - 1];
      const senderText = lastMessage.sender._id === self._id ? "You: " : "";
      contact.lastMessage =
        senderText +
        (lastMessage.type === "text" ? lastMessage.content : "📷 ");
      contact.lastMessageTime = moment(lastMessage.addedOn).calendar();
    }
    return contact;
  };

  return (
    <div className="chat-list">
      {chats
        .sort((chat1, chat2) => {
          const lastMessage1 = chat1.messages[chat1.messages.length - 1];
          const lastMessage2 = chat2.messages[chat2.messages.length - 1];
          return lastMessage2.addedOn.localeCompare(lastMessage1.addedOn);
        })
        .map((chat) => (
          <ChatCard
            key={chat._id}
            _id={chat._id}
            chat={privateChatToCard(chat, self)}
            onChatSelect={onChatSelect}
          />
        ))}
    </div>
  );
}

export default ChatList;
