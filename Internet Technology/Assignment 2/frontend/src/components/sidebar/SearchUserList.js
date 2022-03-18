import React, { useState, useEffect } from "react";
import userService from "../../services/userService";
import UserCard from "../common/UserCard";

function SearchUserList(props) {
  const { onNewUserSelect, searchString } = props;
  const [newUsers, setNewUsers] = useState([]);

  useEffect(() => {
    async function searchUsers() {
      if (searchString !== "") {
        const { data: users } = await userService.search(searchString);
        setNewUsers(users);
      }
    }
    searchUsers();
  }, [searchString]);

  return (
    <div className="chat-list">
      {newUsers.map((newUser) => (
        <UserCard
          key={newUser._id}
          user={newUser}
          onUserSelect={onNewUserSelect}
        />
      ))}
    </div>
  );
}

export default SearchUserList;
