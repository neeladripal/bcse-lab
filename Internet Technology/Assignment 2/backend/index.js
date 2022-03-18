const express = require("express");
const app = express();
const server = require("http").createServer(app);

require("./startup/config")(app);
const logger = require("./startup/logging");
require("./startup/db")();
require("./startup/socket")(server);
require("./startup/routes")(app);
require("./startup/validation");

const port = process.env.PORT;
server.listen(port, () => logger.info(`Listening on port ${port}...`));
