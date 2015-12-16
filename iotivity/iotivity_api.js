// ============================================================================
//  __  __                                  _ _     _
// |  \/  | ___  ___ ___  __ _  __ _  ___  | (_)___| |_ ___ _ __   ___ _ __
// | |\/| |/ _ \/ __/ __|/ _` |/ _` |/ _ \ | | / __| __/ _ \ '_ \ / _ \ '__|
// | |  | |  __/\__ \__ \ (_| | (_| |  __/ | | \__ \ ||  __/ | | |  __/ |
// |_|  |_|\___||___/___/\__,_|\__, |\___| |_|_|___/\__\___|_| |_|\___|_|
//                             |___/
// ============================================================================

var iotivityListener = null;
extension.setMessageListener(function(msg) {
    if (iotivityListener instanceof Function) {
        iotivityListener(msg);
    };
});


// ============================================================================
//  _   _ _   _ _ _ _   _
// | | | | |_(_) (_) |_(_) ___  ___
// | | | | __| | | | __| |/ _ \/ __|
// | |_| | |_| | | | |_| |  __/\__ \
//  \___/ \__|_|_|_|\__|_|\___||___/
//
// ============================================================================
//
exports.__utils = function() {
    this.sendSyncMessage = function(msg) {
        extension.internal.sendSyncMessage(JSON.stringify(msg));
    }
};


// ============================================================================
//  _                       _                _      _    ____ ___
// | |    _____      __    | | _____   _____| |    / \  |  _ \_ _|
// | |   / _ \ \ /\ / /____| |/ _ \ \ / / _ \ |   / _ \ | |_) | |
// | |__| (_) \ V  V /_____| |  __/\ V /  __/ |  / ___ \|  __/| |
// |_____\___/ \_/\_/      |_|\___| \_/ \___|_| /_/   \_\_|  |___|
//
// ============================================================================

exports.lowleverl = function() {
    this.OCInit = function() {
        return iotivity.__utils.sendSyncMessage({
            method: "OCInit",
            args: []
        });
    };
};
