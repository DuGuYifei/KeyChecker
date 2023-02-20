package backend.keychecker.key.dto;

import backend.keychecker.key.entity.Key;
import lombok.*;

import java.util.function.BiFunction;

@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
public class UpdateBindKeyRequest {

    private String key_str;

    private String mac_hash;

    public static BiFunction<Key, String, Key> dtoToEntityUpdater() {
        return (key, mac_hash) -> {
            key.setMacHash(mac_hash);
            return key;
        };
    }

}
