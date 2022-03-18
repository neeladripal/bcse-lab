import React from "react";

function ProfileHeader(props) {
  const { chat, onProfileHeaderClick } = props;
  return (
    <div className="profile-header" onClick={onProfileHeaderClick}>
      <div className="info">
        <img
          src={chat.avatar || process.env.PUBLIC_URL + "avatar.png"}
          alt=""
          className="avatar"
        />
        <span className="name">{chat.name}</span>
      </div>
    </div>
  );
}

export default ProfileHeader;
