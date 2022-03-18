import React, { useState } from "react";
import userService from "../services/userService";
import authService from "../services/authService";
import styled from "styled-components";
import { toast } from "react-toastify";

const User = () => {
  const [forSignUp, setForSignUp] = useState(false);
  const [loading, setLoading] = useState(false);
  const [account, setAccount] = useState({ name: "", email: "", password: "" });

  const handleChange = ({ currentTarget: input }) => {
    const newAccount = { ...account };
    newAccount[input.name] = input.value;
    setAccount(newAccount);
  };

  const trimValues = () => {
    const newAccount = { ...account };
    newAccount.name = newAccount.name.trim();
    newAccount.email = newAccount.email.trim();
    return newAccount;
  };

  const validateFields = ({ name, email, password }) => {
    const newErrors = {};
    if (forSignUp) {
      if (name === "") newErrors.name = "Name is required.";
      else if (name > 20) {
        newErrors.name = "Name can be at most 20 characters long.";
      }
    }

    if (email === "") newErrors.email = "Email is required.";
    else if (email.length > 50) {
      newErrors.email = "Email can be at most 50 characters long.";
    }

    if (password === "") newErrors.password = "Password is required.";
    else if (password.length < 4 || password.length > 50) {
      newErrors.password =
        "Password length must be between 4 and 50 characters.";
    }
    return Object.keys(newErrors).length === 0 ? null : newErrors;
  };

  const validate = () => {
    const newAccount = trimValues();
    setAccount(newAccount);
    const newErrors = validateFields(newAccount);
    if (newErrors)
      for (let key of Object.keys(newErrors)) toast.error(newErrors[key]);
    return newErrors ? false : true;
  };

  const handleRegister = async (e) => {
    e.preventDefault();
    setLoading(true);
    if (!validate()) {
      setLoading(false);
      return;
    }

    // Call the server
    try {
      const response = await userService.register(account);
      authService.loginWithJwt(response.headers["x-auth-token"], response.data);
      window.location = "/";
    } catch (ex) {
      if (ex.response && ex.response.status === 400) {
        toast.error(ex.response.data);
      }
      setLoading(false);
    }
  };

  const handleLogin = async (e) => {
    e.preventDefault();
    setLoading(true);
    if (!validate()) {
      setLoading(false);
      return;
    }

    // Call the server
    try {
      await authService.login(account.email, account.password);
      window.location = "/";
    } catch (ex) {
      if (ex.response && ex.response.status === 400) {
        toast.error(ex.response.data);
      }
      setLoading(false);
    }
  };

  return (
    <>
      <Container>
        <SideImg src={process.env.PUBLIC_URL + "login.png"} alt="" />
        {forSignUp ? (
          <CustomForm>
            <Header>
              <p>
                <img src={process.env.PUBLIC_URL + "chat.png"} alt="" />
                Sign Up
              </p>
              <span onClick={() => setForSignUp(!forSignUp)}>
                Already have an account?
              </span>
            </Header>

            <CustomLogin onSubmit={handleRegister}>
              <input
                type="text"
                placeholder="Name"
                name="name"
                value={account.name}
                onChange={handleChange}
                required
              />
              <input
                type="email"
                placeholder="Email"
                name="email"
                value={account.email}
                onChange={handleChange}
                required
              />
              <input
                type="password"
                placeholder="Password"
                name="password"
                value={account.password}
                onChange={handleChange}
                required
              />

              <div>
                {loading ? (
                  <button>
                    <img
                      src="https://media1.giphy.com/media/L05HgB2h6qICDs5Sms/giphy.gif"
                      alt=""
                    />
                  </button>
                ) : (
                  <button type="submit">Sign up</button>
                )}
              </div>
            </CustomLogin>
          </CustomForm>
        ) : (
          <CustomForm>
            <Header>
              <p>
                <img src={process.env.PUBLIC_URL + "chat.png"} alt="" />
                Sign in
              </p>
              <span onClick={() => setForSignUp(!forSignUp)}>
                create an account
              </span>
            </Header>

            <CustomLogin onSubmit={handleLogin}>
              <input
                type="email"
                placeholder="Email"
                name="email"
                value={account.email}
                onChange={handleChange}
                required
              />
              <input
                type="password"
                placeholder="Password"
                name="password"
                value={account.password}
                onChange={handleChange}
                required
              />

              <div>
                {loading ? (
                  <button>
                    <img
                      src="https://media1.giphy.com/media/L05HgB2h6qICDs5Sms/giphy.gif"
                      alt=""
                    />
                  </button>
                ) : (
                  <button type="submit"> Sign in</button>
                )}
              </div>
            </CustomLogin>
          </CustomForm>
        )}
      </Container>
    </>
  );
};

export default User;

const Container = styled.div`
  min-height: 85vh;
  display: flex;
  justify-content: center;
  align-items: center;
  padding-bottom: 2rem;

  @media (min-width: 900px) {
    min-height: calc(100vh - 62px);
  }
`;

const CustomForm = styled.div`
  height: auto;
  width: 388.797px;
  background-color: #fff;
  padding: 1rem;
  padding-bottom: 2.5rem;
  border-radius: 6px;
  box-shadow: 1px 1px 20px 0px #ebe5e5;

  @media (max-width: 860px) {
    width: 90vw;
  }

  @media (min-width: 1600px) {
    width: 27vw;
  }
`;

const Header = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 2rem;

  p {
    font-size: 1.15rem;
    font-weight: 500;
    display: flex;
    align-items: center;

    img {
      height: 2rem;
    }
  }

  span {
    font-size: 0.78rem;
    cursor: pointer;
    color: #478778;
    text-decoration: none;

    &:hover {
      text-decoration: underline;
    }
  }
`;

const CustomLogin = styled.form`
  input {
    width: 95%;
    padding: 0.5rem;
    font-size: 1rem;
    outline: none;
    margin-top: 0.6rem;
    border: none;
    border-bottom: 1px solid #d5c5c5;
  }

  div {
    display: flex;
    justify-content: center;
    align-items: center;
    margin-top: 30px;

    a {
      font-size: 0.75rem;
      text-decoration: none;
      color: violet;
      cursor: pointer;

      &:hover {
        text-decoration: underline;
      }
    }

    button {
      padding: 0.5rem;
      min-width: 85px;
      border: none;
      background: linear-gradient(#008000, #2e8b57);
      border-radius: 20px;
      color: white;
      font-weight: 500;
      cursor: pointer;
      display: grid;
      place-items: center;

      img {
        height: 1.4rem;
      }
    }
  }

  p {
    font-size: 0.7rem;
    line-height: 0.84rem;
    margin-top: 0.8rem;
  }
`;
const SideImg = styled.img`
  width: 27vw;
  margin-right: 5rem;

  @media (max-width: 900px) {
    display: none;
  }

  @media (max-width: 1000px) {
    margin-right: 2vw;
  }

  @media (min-width: 1600px) {
    width: 27vw;
  }
`;
