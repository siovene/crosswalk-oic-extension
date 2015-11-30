var echoListener = null;
extension.setMessageListener(function(msg) {
  if (echoListener instanceof Function) {
    echoListener(msg);
  };
});

exports.echo = function(msg, callback) {
  echoListener = callback;
  extension.postMessage(msg);
};

exports.syncEcho = function(msg) {
  return extension.internal.sendSyncMessage(msg);
};
