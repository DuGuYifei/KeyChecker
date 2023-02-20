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
public class GetCheckKeyResponse {

    private String key_str;

    private Timestamp expire;

    private String mac_hash;

    public static Function<Key, GetCheckKeyResponse> entityToDtoMapper() {
        return key -> GetCheckKeyResponse.builder()
                .key_str(key.getKeyStr())
                .expire(key.getExpire())
                .mac_hash(key.getMacHash())
                .build();
    }

}
