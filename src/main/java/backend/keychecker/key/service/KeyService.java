package backend.keychecker.key.service;

import backend.keychecker.key.entity.Key;
import backend.keychecker.key.repository.KeyRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.*;

@Service
public class KeyService {

    private final KeyRepository keyRepository;

    @Autowired
    public KeyService(KeyRepository keyRepository) {
        this.keyRepository = keyRepository;
    }

    public Optional<Key> find(long id) { return keyRepository.findById(id); }

    public List<Key> findByKeyStr(String key) {
        return keyRepository.findByKeyStr(key);
    }

    public List<Key> findByUser(String user) {
        return keyRepository.findByUser(user);
    }

    public List<Key> findAll() {
        return keyRepository.findAll();
    }

    @Transactional
    public Key create(Key key) {
        return keyRepository.save(key);
    }

    @Transactional
    public void update(Key key) {
        keyRepository.save(key);
    }

    @Transactional
    public void delete(Long id) {
        keyRepository.deleteById(id);
    }
}
