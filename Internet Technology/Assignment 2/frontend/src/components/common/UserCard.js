import React from "react";

function UserCard(props) {
  const { user, onUserSelect } = props;
  const { name, email, profilePic } = user;
  return (
    <div className="chat-card" onClick={(e) => onUserSelect(user)}>
      <img
        src={profilePic || process.env.PUBLIC_URL + "avatar.png"}
        alt=""
        className="avatar"
      />
      <div className="info">
        <span className="name">{name}</span>
        <span className="subtitle">{email}</span>
      </div>
    </div>
  );
}

export default UserCard;
