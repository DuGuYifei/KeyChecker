package backend.keychecker.key.dto;

import backend.keychecker.key.entity.Key;
import lombok.*;

import java.sql.Timestamp;
import java.util.Collection;
import java.util.List;
import java.util.function.Function;

@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
public class GetKeysResponse {

    @Getter
    @Setter
    @Builder
    @NoArgsConstructor
    @AllArgsConstructor(access = AccessLevel.PRIVATE)
    @ToString
    @EqualsAndHashCode
    public static class KeyItem {

        private long id;

        private String key_str;

        private String user;

        private Timestamp expire;

        private String mac_hash;

    }

    @Singular
    private List<KeyItem> keyItems;

    public static Function<Collection<Key>, GetKeysResponse> entityToDtoMapper() {
        return keys -> {
            GetKeysResponseBuilder responseBuilder = GetKeysResponse.builder();
            keys.stream().
                    map(key -> KeyItem.builder()
                            .id(key.getId())
                            .key_str(key.getKeyStr())
                            .user(key.getUser())
                            .expire(key.getExpire())
                            .mac_hash(key.getMacHash())
                            .build())
                    .forEach(responseBuilder::keyItem);
            return responseBuilder.build();
        };
    }

}
