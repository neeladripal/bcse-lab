require("dotenv").config();
const cors = require("cors");

module.exports = function (app) {
  app.use(
    cors({
      origin: process.env.CLIENT_URI,
    })
  );
  // in case the jwtPrivateKey environment variable is not defined
  if (!process.env.jwtPrivateKey) {
    throw new Error("FATAL ERROR: jwtPrivateKey is not defined");
  }
};
