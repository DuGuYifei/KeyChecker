package backend.keychecker.key.repository;

import backend.keychecker.key.entity.Key;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface KeyRepository extends JpaRepository<Key, Long> {

    List<Key> findByKeyStr(String keyStr);
    List<Key> findByUser(String user);

}
