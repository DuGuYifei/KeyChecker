package backend.keychecker.key.dto;


import backend.keychecker.key.entity.Key;
import lombok.*;

import java.sql.Timestamp;
import java.util.function.Function;

@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
public class GetKeyResponse {

    private long id;

    private String key_str;

    private String user;

    private Timestamp expire;

    private String mac_hash;

    public static Function<Key, GetKeyResponse> entityToDtoMapper(){
        return key -> GetKeyResponse.builder()
                .id(key.getId())
                .key_str(key.getKeyStr())
                .user(key.getUser())
                .expire(key.getExpire())
                .mac_hash(key.getMacHash())
                .build();
    }

}
