const mongoose = require("mongoose");
const Joi = require("joi");
const jwt = require("jsonwebtoken");

const userSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true,
    minlength: 2,
    maxlength: 50,
  },
  email: {
    type: String,
    required: true,
  },
  password: {
    type: String,
    required: true,
  },
  profilePic: {
    type: String,
    default: "",
  },
  addedOn: {
    type: Date,
    default: Date.now,
  },
});

userSchema.methods.generateAuthToken = function () {
  // generate a json web token with _id as payload as
  // environment variable jwtPrivateKey as the private key
  const token = jwt.sign(
    {
      _id: this._id,
      email: this.email,
    },
    process.env.jwtPrivateKey
  );
  return token;
};

const User = mongoose.model("user", userSchema);

function validateUser(user) {
  const schema = Joi.object({
    name: Joi.string().min(5).max(50).required(),
    email: Joi.string().min(5).max(255).email().required(),
    password: Joi.string().min(5).max(255).required(),
    profilePic: Joi.string(),
  });

  return schema.validate(user);
}

function validateEmail(email) {
  const schema = Joi.string().min(5).max(255).email().required();
  return schema.validate(email);
}

exports.User = User;
exports.validate = validateUser;
exports.userSchema = userSchema;
