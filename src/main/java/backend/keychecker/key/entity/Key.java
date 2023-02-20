package backend.keychecker.key.entity;

import lombok.*;

import javax.persistence.*;
import java.io.Serializable;
import java.sql.Timestamp;

@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
@Entity
@Table(name = "t_keys")
public class Key implements Serializable {

    @Id
    @GeneratedValue(strategy = GenerationType.TABLE)
    private Long id;

    @Column(name = "key_str", unique = true, nullable = false, length = 256)
    private String keyStr;

    @Column(nullable = false)
    private String user;

    @Column(nullable = false)
    private Timestamp expire;

    @Column(name = "mac_hash", length = 256)
    private String macHash;


}
