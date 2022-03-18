require("express-async-errors");
const { createLogger, transports, format } = require("winston");

module.exports = createLogger({
  transports: [new transports.Console({ format: format.simple() })],
  exceptionHandlers: [
    new transports.Console({ format: format.simple() }),
    new transports.File({ filename: "exceptions.log" }),
  ],
});
