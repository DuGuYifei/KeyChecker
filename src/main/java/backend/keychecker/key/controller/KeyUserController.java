package backend.keychecker.key.controller;


import backend.keychecker.digest.Sha256;
import backend.keychecker.key.dto.UpdateBindKeyRequest;
import backend.keychecker.key.entity.Key;
import backend.keychecker.key.service.KeyService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Date;
import java.util.List;

@RestController
@RequestMapping("api/keys")
public class KeyUserController {

    private final KeyService keyService;

    @Autowired
    public KeyUserController(KeyService keyService) {
        this.keyService = keyService;
    }

    @PutMapping("/key-check")
    public ResponseEntity<String> updateBindMac(@RequestBody UpdateBindKeyRequest request) {
        List<Key> keys = keyService.findByKeyStr(request.getKey_str());
        if (keys.size() > 0) {
            Key key = keys.get(0);
            String databaseMacHash = key.getMacHash();
            String requestMacHash = Sha256.hash(request.getMac_hash());
            if(key.getExpire().before(new Date()))
                return ResponseEntity.status(HttpStatus.FORBIDDEN).body("密钥已过期(key is expired)");
            if(databaseMacHash == null) {
                key = UpdateBindKeyRequest.dtoToEntityUpdater().apply(key, requestMacHash);
                keyService.update(key);
                return ResponseEntity.accepted().body("机器注册成功(machine register successfully)");
            }else if(databaseMacHash.equals(requestMacHash)){
                return ResponseEntity.accepted().body("机器识别成功(machine recognize successfully)");
            }else{
                return ResponseEntity.status(HttpStatus.FORBIDDEN).body("机器识别失败(machine recognize unsuccessfully)");
            }
        } else {
            return ResponseEntity.notFound().build();
        }
    }

}
