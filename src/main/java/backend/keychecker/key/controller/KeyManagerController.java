package backend.keychecker.key.controller;


import backend.keychecker.key.dto.*;
import backend.keychecker.key.entity.Key;
import backend.keychecker.key.service.KeyService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.util.UriComponentsBuilder;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("api/back-manager/keys")
public class KeyManagerController {

    private final KeyService keyService;

    @Autowired
    public KeyManagerController(KeyService keyService) {
        this.keyService = keyService;
    }

    @GetMapping
    public ResponseEntity<GetKeysResponse> getKeys() {
        return ResponseEntity.ok(GetKeysResponse.entityToDtoMapper().apply(keyService.findAll()));
    }

    @PostMapping
    public ResponseEntity<String> createKey(@RequestBody CreateKeyRequest request, UriComponentsBuilder uriComponentsBuilder) {
        Key key = CreateKeyRequest.dtoToEntityMapper().apply(request);

        key = keyService.create(key);

        return ResponseEntity.created(uriComponentsBuilder
                .pathSegment("api", "back-manager", "keys", "{id}")
                .buildAndExpand(key.getId())
                .toUri()
        ).body(key.getKeyStr());
    }

    @PutMapping("unbind/{id}")
    public ResponseEntity<Void> updateUnbindMac(@PathVariable("id") long id) {
        Optional<Key> key = keyService.find(id);

        if (key.isPresent()) {
            UpdateUnbindMacRequest.dtoToEntityUpdater().apply(key.get());
            keyService.update(key.get());
            return ResponseEntity.accepted().build();
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @PutMapping("edit/{id}")
    public ResponseEntity<Void> updateRenewExpireAndUser(@RequestBody UpdateRenewExpireAndUserRequest request, @PathVariable("id") long id){
        Optional<Key> key = keyService.find(id);

        if (key.isPresent()) {
            UpdateRenewExpireAndUserRequest.dtoToEntityUpdater().apply(key.get(), request);
            keyService.update(key.get());
            return ResponseEntity.accepted().build();
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @GetMapping("key-str/{keyStr}")
    public ResponseEntity<GetKeyResponse> getKeyByKeyStr(@PathVariable("keyStr") String keyStr) {
        List<Key> keys =  keyService.findByKeyStr(keyStr);
        if(keys.size() == 0)
            return ResponseEntity.notFound().build();
        Key key = keys.get(0);
        return ResponseEntity.ok(GetKeyResponse.entityToDtoMapper().apply(key));
    }

    @GetMapping("user/{username}")
    public ResponseEntity<GetKeyResponse> getKeyByUser(@PathVariable("username") String user) {
        List<Key> keys = keyService.findByUser(user);
        if(keys.size() == 0)
            return ResponseEntity.notFound().build();
        Key key = keys.get(0);
        return ResponseEntity.ok(GetKeyResponse.entityToDtoMapper().apply(key));
    }

    @DeleteMapping("{id}")
    public ResponseEntity<Void> deleteKey(@PathVariable("id") long id) {
        Optional<Key> key = keyService.find(id);
        if (key.isPresent()) {
            keyService.delete(key.get().getId());
            return ResponseEntity.accepted().build();
        } else {
            return ResponseEntity.notFound().build();
        }
    }

}
