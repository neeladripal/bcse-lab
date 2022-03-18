import React from "react";
import auth from "../services/authService";

function UserDetails(props) {
  const { user } = props;

  const handleLogout = (e) => {
    auth.logout();
    window.location = "/";
  };

  return (
    <div className="user-details">
      <img
        alt="PROFILE_PIC"
        src={
          user.profilePic
            ? user.profilePic
            : process.env.PUBLIC_URL + "avatar.png"
        }
      />
      <span>{user.name}</span>
      {user.email}
      <div className="logout" onClick={handleLogout}>
        Logout
      </div>
    </div>
  );
}

export default UserDetails;
