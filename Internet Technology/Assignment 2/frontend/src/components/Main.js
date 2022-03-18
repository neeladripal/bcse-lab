import React, { useState, useEffect } from "react";
import SideBar from "./sidebar/SideBar";
import Chat from "./chat/Chat";
import UserDetails from "./UserDetails";
import chatService from "../services/chatService";
import socket from "../services/socket";
import { toast } from "react-toastify";

function Main(props) {
  const { user } = props;
  const [selectedChat, setSelectedChat] = useState();
  const [chats, setChats] = useState([]);
  const [globalChat, setGlobalChat] = useState({
    _id: "global",
    messages: [],
    type: "global",
  });

  useEffect(() => {
    function initSocket(userId) {
      socket.auth = { userId };
      socket.connect();
      socket.on("connect_error", (err) => {
        toast.error("Internet disconnected");
      });
    }

    async function fetchChannels() {
      try {
        const { data: newChats } = await chatService.getChats();
        setChats(newChats);
      } catch (ex) {
        toast.error(ex.response.data);
      }
    }

    async function fetchGlobalMessages() {
      try {
        const { data: newGlobalMessages } =
          await chatService.getGlobalMessages();
        setGlobalChat((globalChat) => {
          return { ...globalChat, messages: newGlobalMessages };
        });
      } catch (ex) {
        toast.error(ex.response.data);
      }
    }

    initSocket(user._id);
    fetchChannels();
    fetchGlobalMessages();

    return () => {
      socket.off("connect_error");
    };
  }, [user._id]);

  const handleProfileHeaderClick = () => {
    setSelectedChat(null);
  };

  const handleNewUserSelect = (user) => {
    const chatExisting = chats.find((chat) => chat.users[0]._id === user._id);
    if (chatExisting) setSelectedChat(chatExisting);
    else {
      setSelectedChat({
        _id: null,
        users: [user],
        messages: [],
        type: "private",
      });
    }
  };

  const handleChatSelect = (chatId) => {
    if (chatId === "global") {
      setSelectedChat(globalChat);
    } else {
      const newChat = chats.find((chat) => chat._id === chatId);
      setSelectedChat(newChat);
    }
  };

  const handleMessageSend = async (message) => {
    try {
      const chatId = selectedChat._id;
      if (chatId) {
        message.channelId = chatId;
      } else {
        const receiver = selectedChat.users[0];
        const { data: newChat } = await chatService.createChat([
          user.email,
          receiver.email,
        ]);
        message.channelId = newChat._id;
      }
      message.senderName = user.name;

      if (chatId === "global") {
        socket.emit("global_message", { body: message }, (err) =>
          console.log(err)
        );
      } else {
        socket.emit("private_message", { body: message }, (err) =>
          console.log(err)
        );
      }
    } catch (ex) {
      toast.error(ex.response.data);
    }
  };

  useEffect(() => {
    socket.on("global_message", ({ body, from }) => {
      let newGlobalChat;

      setGlobalChat((globalChat) => {
        newGlobalChat = {
          ...globalChat,
          messages: [...globalChat.messages, body],
        };
        return newGlobalChat;
      });

      setSelectedChat((selectedChat) => {
        if (selectedChat && selectedChat._id && selectedChat._id === "global")
          return newGlobalChat;
        else return selectedChat;
      });
    });

    socket.on("private_message", async ({ body, from }) => {
      let tempChats;
      setChats((chats) => {
        tempChats = chats;
        return chats;
      });
      const index = tempChats.findIndex((chat) => chat._id === from);
      let newChat;
      let newChats;
      if (index === -1) {
        try {
          const { data } = await chatService.getChat(from);
          newChat = data;
          newChats = [newChat, ...tempChats];
        } catch (ex) {
          if (ex.response) console.log(ex.response.data);
        }
      } else {
        newChats = [...tempChats];
        newChat = newChats[index];
        newChat.messages = [...newChat.messages, body];
      }
      setChats(newChats);

      setSelectedChat((selectedChat) => {
        if (
          selectedChat &&
          ((selectedChat._id && selectedChat._id === from) ||
            (selectedChat.type === "private" &&
              selectedChat.users[0]._id === newChat.users[0]._id))
        )
          return newChat;
        else return selectedChat;
      });
    });

    return () => {
      socket.off("private_message");
      socket.off("global_message");
    };
  }, []);

  return (
    <div className="Main">
      <SideBar
        onProfileHeaderClick={handleProfileHeaderClick}
        onChatSelect={handleChatSelect}
        onNewUserSelect={handleNewUserSelect}
        self={user}
        chats={chats}
        globalChat={globalChat}
      />
      {selectedChat ? (
        <Chat
          selectedChat={selectedChat}
          self={user}
          onMessageSend={handleMessageSend}
        />
      ) : (
        <UserDetails user={user} />
      )}
    </div>
  );
}

export default Main;
