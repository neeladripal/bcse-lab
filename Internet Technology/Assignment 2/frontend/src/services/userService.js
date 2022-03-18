import http from "./httpService";

const apiEndpoint = process.env.REACT_APP_SERVER_URL + "/api/users";

function register(user) {
  return http.post(apiEndpoint, {
    name: user.name,
    email: user.email,
    password: user.password,
  });
}

function search(key) {
  return http.get(`${apiEndpoint}/search?key=${key}`);
}

const userService = {
  register,
  search,
};

export default userService;
