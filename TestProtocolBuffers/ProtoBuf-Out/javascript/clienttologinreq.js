// source: tutorial.hierarchy.proto
/**
 * @fileoverview
 * @enhanceable
 * @suppress {missingRequire} reports error on implicit type usages.
 * @suppress {messageConventions} JS Compiler reports an error if a variable or
 *     field starts with 'MSG_' and isn't a translatable message.
 * @public
 */
// GENERATED CODE -- DO NOT EDIT!
/* eslint-disable */
// @ts-nocheck

goog.provide('proto.ClientToLoginReq');
goog.provide('proto.ClientToLoginReq.LoginReq');
goog.provide('proto.ClientToLoginReq.LogoutReq');
goog.provide('proto.ClientToLoginReq.MsgCase');

goog.require('jspb.BinaryReader');
goog.require('jspb.BinaryWriter');
goog.require('jspb.Message');

/**
 * Generated by JsPbCodeGenerator.
 * @param {Array=} opt_data Optional initial data array, typically from a
 * server response, or constructed directly in Javascript. The array is used
 * in place and becomes part of the constructed object. It is not cloned.
 * If no data is provided, the constructed object will be empty, but still
 * valid.
 * @extends {jspb.Message}
 * @constructor
 */
proto.ClientToLoginReq = function(opt_data) {
  jspb.Message.initialize(this, opt_data, 0, -1, null, proto.ClientToLoginReq.oneofGroups_);
};
goog.inherits(proto.ClientToLoginReq, jspb.Message);
if (goog.DEBUG && !COMPILED) {
  /**
   * @public
   * @override
   */
  proto.ClientToLoginReq.displayName = 'proto.ClientToLoginReq';
}
/**
 * Generated by JsPbCodeGenerator.
 * @param {Array=} opt_data Optional initial data array, typically from a
 * server response, or constructed directly in Javascript. The array is used
 * in place and becomes part of the constructed object. It is not cloned.
 * If no data is provided, the constructed object will be empty, but still
 * valid.
 * @extends {jspb.Message}
 * @constructor
 */
proto.ClientToLoginReq.LoginReq = function(opt_data) {
  jspb.Message.initialize(this, opt_data, 0, -1, null, null);
};
goog.inherits(proto.ClientToLoginReq.LoginReq, jspb.Message);
if (goog.DEBUG && !COMPILED) {
  /**
   * @public
   * @override
   */
  proto.ClientToLoginReq.LoginReq.displayName = 'proto.ClientToLoginReq.LoginReq';
}
/**
 * Generated by JsPbCodeGenerator.
 * @param {Array=} opt_data Optional initial data array, typically from a
 * server response, or constructed directly in Javascript. The array is used
 * in place and becomes part of the constructed object. It is not cloned.
 * If no data is provided, the constructed object will be empty, but still
 * valid.
 * @extends {jspb.Message}
 * @constructor
 */
proto.ClientToLoginReq.LogoutReq = function(opt_data) {
  jspb.Message.initialize(this, opt_data, 0, -1, null, null);
};
goog.inherits(proto.ClientToLoginReq.LogoutReq, jspb.Message);
if (goog.DEBUG && !COMPILED) {
  /**
   * @public
   * @override
   */
  proto.ClientToLoginReq.LogoutReq.displayName = 'proto.ClientToLoginReq.LogoutReq';
}

/**
 * Oneof group definitions for this message. Each group defines the field
 * numbers belonging to that group. When of these fields' value is set, all
 * other fields in the group are cleared. During deserialization, if multiple
 * fields are encountered for a group, only the last value seen will be kept.
 * @private {!Array<!Array<number>>}
 * @const
 */
proto.ClientToLoginReq.oneofGroups_ = [[1,2]];

/**
 * @enum {number}
 */
proto.ClientToLoginReq.MsgCase = {
  MSG_NOT_SET: 0,
  LOGINREQ: 1,
  LOGOUTREQ: 2
};

/**
 * @return {proto.ClientToLoginReq.MsgCase}
 */
proto.ClientToLoginReq.prototype.getMsgCase = function() {
  return /** @type {proto.ClientToLoginReq.MsgCase} */(jspb.Message.computeOneofCase(this, proto.ClientToLoginReq.oneofGroups_[0]));
};



if (jspb.Message.GENERATE_TO_OBJECT) {
/**
 * Creates an object representation of this proto.
 * Field names that are reserved in JavaScript and will be renamed to pb_name.
 * Optional fields that are not set will be set to undefined.
 * To access a reserved field use, foo.pb_<name>, eg, foo.pb_default.
 * For the list of reserved names please see:
 *     net/proto2/compiler/js/internal/generator.cc#kKeyword.
 * @param {boolean=} opt_includeInstance Deprecated. whether to include the
 *     JSPB instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @return {!Object}
 */
proto.ClientToLoginReq.prototype.toObject = function(opt_includeInstance) {
  return proto.ClientToLoginReq.toObject(opt_includeInstance, this);
};


/**
 * Static version of the {@see toObject} method.
 * @param {boolean|undefined} includeInstance Deprecated. Whether to include
 *     the JSPB instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @param {!proto.ClientToLoginReq} msg The msg instance to transform.
 * @return {!Object}
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.ClientToLoginReq.toObject = function(includeInstance, msg) {
  var f, obj = {
    loginreq: (f = msg.getLoginreq()) && proto.ClientToLoginReq.LoginReq.toObject(includeInstance, f),
    logoutreq: (f = msg.getLogoutreq()) && proto.ClientToLoginReq.LogoutReq.toObject(includeInstance, f)
  };

  if (includeInstance) {
    obj.$jspbMessageInstance = msg;
  }
  return obj;
};
}


/**
 * Deserializes binary data (in protobuf wire format).
 * @param {jspb.ByteSource} bytes The bytes to deserialize.
 * @return {!proto.ClientToLoginReq}
 */
proto.ClientToLoginReq.deserializeBinary = function(bytes) {
  var reader = new jspb.BinaryReader(bytes);
  var msg = new proto.ClientToLoginReq;
  return proto.ClientToLoginReq.deserializeBinaryFromReader(msg, reader);
};


/**
 * Deserializes binary data (in protobuf wire format) from the
 * given reader into the given message object.
 * @param {!proto.ClientToLoginReq} msg The message object to deserialize into.
 * @param {!jspb.BinaryReader} reader The BinaryReader to use.
 * @return {!proto.ClientToLoginReq}
 */
proto.ClientToLoginReq.deserializeBinaryFromReader = function(msg, reader) {
  while (reader.nextField()) {
    if (reader.isEndGroup()) {
      break;
    }
    var field = reader.getFieldNumber();
    switch (field) {
    case 1:
      var value = new proto.ClientToLoginReq.LoginReq;
      reader.readMessage(value,proto.ClientToLoginReq.LoginReq.deserializeBinaryFromReader);
      msg.setLoginreq(value);
      break;
    case 2:
      var value = new proto.ClientToLoginReq.LogoutReq;
      reader.readMessage(value,proto.ClientToLoginReq.LogoutReq.deserializeBinaryFromReader);
      msg.setLogoutreq(value);
      break;
    default:
      reader.skipField();
      break;
    }
  }
  return msg;
};


/**
 * Serializes the message to binary data (in protobuf wire format).
 * @return {!Uint8Array}
 */
proto.ClientToLoginReq.prototype.serializeBinary = function() {
  var writer = new jspb.BinaryWriter();
  proto.ClientToLoginReq.serializeBinaryToWriter(this, writer);
  return writer.getResultBuffer();
};


/**
 * Serializes the given message to binary data (in protobuf wire
 * format), writing to the given BinaryWriter.
 * @param {!proto.ClientToLoginReq} message
 * @param {!jspb.BinaryWriter} writer
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.ClientToLoginReq.serializeBinaryToWriter = function(message, writer) {
  var f = undefined;
  f = message.getLoginreq();
  if (f != null) {
    writer.writeMessage(
      1,
      f,
      proto.ClientToLoginReq.LoginReq.serializeBinaryToWriter
    );
  }
  f = message.getLogoutreq();
  if (f != null) {
    writer.writeMessage(
      2,
      f,
      proto.ClientToLoginReq.LogoutReq.serializeBinaryToWriter
    );
  }
};





if (jspb.Message.GENERATE_TO_OBJECT) {
/**
 * Creates an object representation of this proto.
 * Field names that are reserved in JavaScript and will be renamed to pb_name.
 * Optional fields that are not set will be set to undefined.
 * To access a reserved field use, foo.pb_<name>, eg, foo.pb_default.
 * For the list of reserved names please see:
 *     net/proto2/compiler/js/internal/generator.cc#kKeyword.
 * @param {boolean=} opt_includeInstance Deprecated. whether to include the
 *     JSPB instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @return {!Object}
 */
proto.ClientToLoginReq.LoginReq.prototype.toObject = function(opt_includeInstance) {
  return proto.ClientToLoginReq.LoginReq.toObject(opt_includeInstance, this);
};


/**
 * Static version of the {@see toObject} method.
 * @param {boolean|undefined} includeInstance Deprecated. Whether to include
 *     the JSPB instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @param {!proto.ClientToLoginReq.LoginReq} msg The msg instance to transform.
 * @return {!Object}
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.ClientToLoginReq.LoginReq.toObject = function(includeInstance, msg) {
  var f, obj = {
    id: jspb.Message.getFieldWithDefault(msg, 1, ""),
    password: jspb.Message.getFieldWithDefault(msg, 2, ""),
    securtytoken: jspb.Message.getFieldWithDefault(msg, 3, "")
  };

  if (includeInstance) {
    obj.$jspbMessageInstance = msg;
  }
  return obj;
};
}


/**
 * Deserializes binary data (in protobuf wire format).
 * @param {jspb.ByteSource} bytes The bytes to deserialize.
 * @return {!proto.ClientToLoginReq.LoginReq}
 */
proto.ClientToLoginReq.LoginReq.deserializeBinary = function(bytes) {
  var reader = new jspb.BinaryReader(bytes);
  var msg = new proto.ClientToLoginReq.LoginReq;
  return proto.ClientToLoginReq.LoginReq.deserializeBinaryFromReader(msg, reader);
};


/**
 * Deserializes binary data (in protobuf wire format) from the
 * given reader into the given message object.
 * @param {!proto.ClientToLoginReq.LoginReq} msg The message object to deserialize into.
 * @param {!jspb.BinaryReader} reader The BinaryReader to use.
 * @return {!proto.ClientToLoginReq.LoginReq}
 */
proto.ClientToLoginReq.LoginReq.deserializeBinaryFromReader = function(msg, reader) {
  while (reader.nextField()) {
    if (reader.isEndGroup()) {
      break;
    }
    var field = reader.getFieldNumber();
    switch (field) {
    case 1:
      var value = /** @type {string} */ (reader.readString());
      msg.setId(value);
      break;
    case 2:
      var value = /** @type {string} */ (reader.readString());
      msg.setPassword(value);
      break;
    case 3:
      var value = /** @type {string} */ (reader.readString());
      msg.setSecurtytoken(value);
      break;
    default:
      reader.skipField();
      break;
    }
  }
  return msg;
};


/**
 * Serializes the message to binary data (in protobuf wire format).
 * @return {!Uint8Array}
 */
proto.ClientToLoginReq.LoginReq.prototype.serializeBinary = function() {
  var writer = new jspb.BinaryWriter();
  proto.ClientToLoginReq.LoginReq.serializeBinaryToWriter(this, writer);
  return writer.getResultBuffer();
};


/**
 * Serializes the given message to binary data (in protobuf wire
 * format), writing to the given BinaryWriter.
 * @param {!proto.ClientToLoginReq.LoginReq} message
 * @param {!jspb.BinaryWriter} writer
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.ClientToLoginReq.LoginReq.serializeBinaryToWriter = function(message, writer) {
  var f = undefined;
  f = message.getId();
  if (f.length > 0) {
    writer.writeString(
      1,
      f
    );
  }
  f = message.getPassword();
  if (f.length > 0) {
    writer.writeString(
      2,
      f
    );
  }
  f = message.getSecurtytoken();
  if (f.length > 0) {
    writer.writeString(
      3,
      f
    );
  }
};


/**
 * optional string id = 1;
 * @return {string}
 */
proto.ClientToLoginReq.LoginReq.prototype.getId = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 1, ""));
};


/**
 * @param {string} value
 * @return {!proto.ClientToLoginReq.LoginReq} returns this
 */
proto.ClientToLoginReq.LoginReq.prototype.setId = function(value) {
  return jspb.Message.setProto3StringField(this, 1, value);
};


/**
 * optional string password = 2;
 * @return {string}
 */
proto.ClientToLoginReq.LoginReq.prototype.getPassword = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 2, ""));
};


/**
 * @param {string} value
 * @return {!proto.ClientToLoginReq.LoginReq} returns this
 */
proto.ClientToLoginReq.LoginReq.prototype.setPassword = function(value) {
  return jspb.Message.setProto3StringField(this, 2, value);
};


/**
 * optional string securtyToken = 3;
 * @return {string}
 */
proto.ClientToLoginReq.LoginReq.prototype.getSecurtytoken = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 3, ""));
};


/**
 * @param {string} value
 * @return {!proto.ClientToLoginReq.LoginReq} returns this
 */
proto.ClientToLoginReq.LoginReq.prototype.setSecurtytoken = function(value) {
  return jspb.Message.setProto3StringField(this, 3, value);
};





if (jspb.Message.GENERATE_TO_OBJECT) {
/**
 * Creates an object representation of this proto.
 * Field names that are reserved in JavaScript and will be renamed to pb_name.
 * Optional fields that are not set will be set to undefined.
 * To access a reserved field use, foo.pb_<name>, eg, foo.pb_default.
 * For the list of reserved names please see:
 *     net/proto2/compiler/js/internal/generator.cc#kKeyword.
 * @param {boolean=} opt_includeInstance Deprecated. whether to include the
 *     JSPB instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @return {!Object}
 */
proto.ClientToLoginReq.LogoutReq.prototype.toObject = function(opt_includeInstance) {
  return proto.ClientToLoginReq.LogoutReq.toObject(opt_includeInstance, this);
};


/**
 * Static version of the {@see toObject} method.
 * @param {boolean|undefined} includeInstance Deprecated. Whether to include
 *     the JSPB instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @param {!proto.ClientToLoginReq.LogoutReq} msg The msg instance to transform.
 * @return {!Object}
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.ClientToLoginReq.LogoutReq.toObject = function(includeInstance, msg) {
  var f, obj = {

  };

  if (includeInstance) {
    obj.$jspbMessageInstance = msg;
  }
  return obj;
};
}


/**
 * Deserializes binary data (in protobuf wire format).
 * @param {jspb.ByteSource} bytes The bytes to deserialize.
 * @return {!proto.ClientToLoginReq.LogoutReq}
 */
proto.ClientToLoginReq.LogoutReq.deserializeBinary = function(bytes) {
  var reader = new jspb.BinaryReader(bytes);
  var msg = new proto.ClientToLoginReq.LogoutReq;
  return proto.ClientToLoginReq.LogoutReq.deserializeBinaryFromReader(msg, reader);
};


/**
 * Deserializes binary data (in protobuf wire format) from the
 * given reader into the given message object.
 * @param {!proto.ClientToLoginReq.LogoutReq} msg The message object to deserialize into.
 * @param {!jspb.BinaryReader} reader The BinaryReader to use.
 * @return {!proto.ClientToLoginReq.LogoutReq}
 */
proto.ClientToLoginReq.LogoutReq.deserializeBinaryFromReader = function(msg, reader) {
  while (reader.nextField()) {
    if (reader.isEndGroup()) {
      break;
    }
    var field = reader.getFieldNumber();
    switch (field) {
    default:
      reader.skipField();
      break;
    }
  }
  return msg;
};


/**
 * Serializes the message to binary data (in protobuf wire format).
 * @return {!Uint8Array}
 */
proto.ClientToLoginReq.LogoutReq.prototype.serializeBinary = function() {
  var writer = new jspb.BinaryWriter();
  proto.ClientToLoginReq.LogoutReq.serializeBinaryToWriter(this, writer);
  return writer.getResultBuffer();
};


/**
 * Serializes the given message to binary data (in protobuf wire
 * format), writing to the given BinaryWriter.
 * @param {!proto.ClientToLoginReq.LogoutReq} message
 * @param {!jspb.BinaryWriter} writer
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.ClientToLoginReq.LogoutReq.serializeBinaryToWriter = function(message, writer) {
  var f = undefined;
};


/**
 * optional LoginReq loginReq = 1;
 * @return {?proto.ClientToLoginReq.LoginReq}
 */
proto.ClientToLoginReq.prototype.getLoginreq = function() {
  return /** @type{?proto.ClientToLoginReq.LoginReq} */ (
    jspb.Message.getWrapperField(this, proto.ClientToLoginReq.LoginReq, 1));
};


/**
 * @param {?proto.ClientToLoginReq.LoginReq|undefined} value
 * @return {!proto.ClientToLoginReq} returns this
*/
proto.ClientToLoginReq.prototype.setLoginreq = function(value) {
  return jspb.Message.setOneofWrapperField(this, 1, proto.ClientToLoginReq.oneofGroups_[0], value);
};


/**
 * Clears the message field making it undefined.
 * @return {!proto.ClientToLoginReq} returns this
 */
proto.ClientToLoginReq.prototype.clearLoginreq = function() {
  return this.setLoginreq(undefined);
};


/**
 * Returns whether this field is set.
 * @return {boolean}
 */
proto.ClientToLoginReq.prototype.hasLoginreq = function() {
  return jspb.Message.getField(this, 1) != null;
};


/**
 * optional LogoutReq logoutReq = 2;
 * @return {?proto.ClientToLoginReq.LogoutReq}
 */
proto.ClientToLoginReq.prototype.getLogoutreq = function() {
  return /** @type{?proto.ClientToLoginReq.LogoutReq} */ (
    jspb.Message.getWrapperField(this, proto.ClientToLoginReq.LogoutReq, 2));
};


/**
 * @param {?proto.ClientToLoginReq.LogoutReq|undefined} value
 * @return {!proto.ClientToLoginReq} returns this
*/
proto.ClientToLoginReq.prototype.setLogoutreq = function(value) {
  return jspb.Message.setOneofWrapperField(this, 2, proto.ClientToLoginReq.oneofGroups_[0], value);
};


/**
 * Clears the message field making it undefined.
 * @return {!proto.ClientToLoginReq} returns this
 */
proto.ClientToLoginReq.prototype.clearLogoutreq = function() {
  return this.setLogoutreq(undefined);
};


/**
 * Returns whether this field is set.
 * @return {boolean}
 */
proto.ClientToLoginReq.prototype.hasLogoutreq = function() {
  return jspb.Message.getField(this, 2) != null;
};

