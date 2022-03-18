import React, { useState } from "react";
import ProfileHeader from "../common/ProfileHeader";
import GlobalChatCard from "./GlobalChatCard";
import Search from "./SearchUsers";
import SearchUserList from "./SearchUserList";
import ChatList from "./ChatList";

function SideBar(props) {
  const {
    self,
    chats,
    globalChat,
    onProfileHeaderClick,
    onChatSelect,
    onNewUserSelect,
  } = props;
  const [searchString, setSearchString] = useState("");

  const handleSearchStringChange = (key) => {
    setSearchString(key);
  };

  const handleNewUserSelect = (user) => {
    setSearchString("");
    onNewUserSelect(user);
  };

  return (
    <div className="sidebar">
      <ProfileHeader chat={self} onProfileHeaderClick={onProfileHeaderClick} />
      <GlobalChatCard
        onChatSelect={onChatSelect}
        globalChat={globalChat}
        self={self}
      />
      <Search
        searchString={searchString}
        onSearchChange={handleSearchStringChange}
      />
      {searchString.trim() === "" ? (
        <ChatList onChatSelect={onChatSelect} chats={chats} self={self} />
      ) : (
        <SearchUserList
          searchString={searchString}
          onNewUserSelect={handleNewUserSelect}
        />
      )}
    </div>
  );
}

export default SideBar;
