import React, { useState, useEffect } from "react";
import Main from "./components/Main";
import User from "./components/User";
import auth from "./services/authService";
import { ToastContainer } from "react-toastify";
import "./App.css";
import "react-toastify/dist/ReactToastify.css";

function App() {
  const [user, setUser] = useState(null);
  useEffect(() => {
    const newUser = auth.getCurrentUser();
    if (newUser) setUser(newUser);
  }, []);
  return (
    <div className="App">
      <ToastContainer />
      {user ? <Main user={user} /> : <User />}
    </div>
  );
}

export default App;
