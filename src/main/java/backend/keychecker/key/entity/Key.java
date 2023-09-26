package backend.keychecker.key.entity;

import backend.keychecker.key.EruptProxy.KeyProxy;
import lombok.*;
import xyz.erupt.annotation.Erupt;
import xyz.erupt.annotation.EruptField;
import xyz.erupt.annotation.sub_erupt.Power;
import xyz.erupt.annotation.sub_field.Edit;
import xyz.erupt.annotation.sub_field.EditType;
import xyz.erupt.annotation.sub_field.View;
import xyz.erupt.annotation.sub_field.sub_edit.DateType;

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
@Erupt(name = "密钥管理", desc = "密钥管理", power = @Power(importable = true, export = true), dataProxy = KeyProxy.class)
public class Key {

    @Id
    @GeneratedValue(strategy = GenerationType.TABLE)
    @EruptField(views = @View(title = "id"))
    private Long id;

    @Column(name = "key_str", unique = true, nullable = false, length = 256)
    @EruptField(views = @View(title = "密钥"))
    private String keyStr;

    @Column(nullable = false)
    @EruptField(views = @View(title = "用户"), edit = @Edit(title = "用户"))
    private String user;

    @Column(nullable = false)
    @EruptField(views = @View(title = "过期时间"), edit = @Edit(title = "过期时间", type = EditType.DATE, dateType = @DateType(type = DateType.Type.DATE_TIME)))
    private Timestamp expire;

    @Column(name = "mac_hash", length = 256)
    @EruptField(views = @View(title = "mac加密值"), edit = @Edit(title = "mac加密值", placeHolder = "新建时不要输入任何值"))
    private String macHash;


}
