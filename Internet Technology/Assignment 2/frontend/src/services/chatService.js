import http from "./httpService";

const apiEndpoint = process.env.REACT_APP_SERVER_URL + "/api";

function getChats() {
  return http.get(apiEndpoint + "/channels");
}

function getChat(chatId) {
  return http.get(apiEndpoint + "/channels/" + chatId);
}

function getGlobalMessages() {
  return http.get(apiEndpoint + "/messages/global");
}

function sendMessage(message) {
  return http.post(apiEndpoint + "/messages/private", message);
}

function sendGlobalMessage(message) {
  return http.post(apiEndpoint + "/messages/global", message);
}

function createChat(users) {
  const requestBody = {
    users: [...users],
    type: "private",
  };
  return http.post(apiEndpoint + "/channels/private", requestBody);
}

const chatService = {
  getChats,
  getChat,
  getGlobalMessages,
  sendMessage,
  sendGlobalMessage,
  createChat,
};

export default chatService;
