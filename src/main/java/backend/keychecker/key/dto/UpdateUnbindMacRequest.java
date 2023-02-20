package backend.keychecker.key.dto;


import backend.keychecker.key.entity.Key;
import lombok.*;

import java.util.function.Function;


@Getter
@Setter
@Builder
@NoArgsConstructor
@ToString
@EqualsAndHashCode
public class UpdateUnbindMacRequest {

    public static Function<Key, Key> dtoToEntityUpdater() {
        return key -> {
            key.setMacHash(null);
            return key;
        };
    }

}
