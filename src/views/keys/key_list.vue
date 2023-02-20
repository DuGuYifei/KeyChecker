<template>
	<div>
		&nbsp;&nbsp;
		<span class="ml-3 w-35 text-gray-600 inline-flex items-center">User name:</span>
		&nbsp;&nbsp;
		<el-input v-model="userCreate" class="w-20 m-2" placeholder="请输入用户名, 必填" style="width: 300px;" />
		&nbsp;&nbsp;
		<el-button type="danger" @click="handleCreate()" :disabled="!userCreate.length">Create</el-button>
	</div>
	<div class="key_table">
		<el-table :data="filterTableData" style="width: 100%" height="87vh">
			<el-table-column fixed prop="id" label="id" width="80" />
			<el-table-column prop="key_str" label="密钥" width="285" />
			<el-table-column prop="user" label="用户名" width="150" />
			<el-table-column prop="mac_hash" label="机器绑定标识符" width="280" />
			<el-table-column prop="expire" label="过期日期" width="210" />
			<el-table-column prop="remain_day" label="剩余天数" width="80" align="center" />
			<el-table-column align="center">
				<template #header>
					<el-input v-model="search" size="small" placeholder="Type to search" />
				</template>
				<template #default="scope">
					<el-button size="small" @click="dialogFormVisible = true; form.dayCount = 30; form.username = scope.row.user; form.id = scope.row.id;">
						编辑用户/重置天数
					</el-button>
					&nbsp;&nbsp;
					<el-button size="small" @click="handleUnbind(scope.row)">解绑设备</el-button>
					&nbsp;&nbsp;
					<el-button size="small" type="danger" @click="handleDelete(scope.row)">Delete</el-button>
				</template>
			</el-table-column>
		</el-table>
		<el-dialog v-model="dialogFormVisible" title="编辑用户/重置天数">
			<el-form :model="form">
				<el-form-item label="用户名" label-width="140px">
					<el-input v-model="form.username" autocomplete="off" style="width: 300px;" />
				</el-form-item>
				<el-form-item label="距今" label-width="140px">
					<el-input-number :min="0" :max="9999" size="small" controls-position="right" v-model="form.dayCount" />&nbsp;&nbsp;天过期
				</el-form-item>

			</el-form>
			<template #footer>
				<span class="dialog-footer">
					<el-button @click="dialogFormVisible = false">Cancel</el-button>
					<el-button type="primary" @click="dialogFormVisible = false; handleReset();">
						Confirm
					</el-button>
				</span>
			</template>
		</el-dialog>

	</div>
</template>


<script lang="ts">
	import {
		computed
	} from 'vue'

	export default {
		data() {
			return {
				search: "",
				filterTableData: [],
				userCreate: "",
				dialogFormVisible: false,
				form: {
					id: -1,
					username: '',
					dayCount: 0,
				},
			}
		},

		methods: {
			handleDelete(row: Key) {
				let that = this;
				const xhttp = new XMLHttpRequest();
				xhttp.onreadystatechange = function() {
					if (this.readyState === 4 && this.status === 202) {
						fetchAndDisplayKeys(that);
					}
				};
				xhttp.open("DELETE", '/api/back-manager/keys/' + row.id, true);
				xhttp.send();
			},

			handleUnbind(row: Key) {
				let that = this;
				const xhttp = new XMLHttpRequest();
				xhttp.onreadystatechange = function() {
					if (this.readyState === 4 && this.status === 202) {
						fetchAndDisplayKeys(that);
					}
				};

				xhttp.open("PUT", '/api/back-manager/keys/unbind/' + row.id, true);

				xhttp.send();
			},

			handleReset() {
				let that = this;
				const xhttp = new XMLHttpRequest();
				xhttp.onreadystatechange = function () {
				    if (this.readyState === 4 && this.status === 202) {
				        fetchAndDisplayKeys(that);
				    }
				};
				xhttp.open("PUT", '/api/back-manager/keys/edit/' + this.form.id, true);

				const request = {
					'user': this.form.username,
					'dayCount': this.form.dayCount,
				};
				xhttp.setRequestHeader('Content-Type', 'application/json');
				xhttp.send(JSON.stringify(request));
			},

			handleCreate() {
				createKey(this);
			},
		},
		mounted() {
			fetchAndDisplayKeys(this);
		},
	};

	class Key {
		id: number
		key_str: string
		user: string
		expire: Date
		mac_hash: string
		remain_day: number

		public constructor(keyItem: any) {
			this.id = keyItem.id;
			this.key_str = keyItem.key_str;
			this.user = keyItem.user;
			this.expire = new Date(keyItem.expire);
			this.mac_hash = keyItem.mac_hash;
			this.remain_day = Math.floor((this.expire - new Date()) / 24 / 3600 / 1000);
		}
	}

	function displayKeys(keyItems: Object[], obj: any) {
		let tableData = [];
		keyItems.forEach(keyItem => {
			tableData.push(new Key(keyItem));

		});
		obj.filterTableData = computed(() =>
			tableData.filter(
				(data) =>
				!obj.search ||
				data.user.toLowerCase().includes(obj.search.toLowerCase()) ||
				data.key_str.includes(obj.search.toLowerCase())
			));
	};

	function fetchAndDisplayKeys(obj: any) {
		const xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function() {
			if (this.readyState === 4 && this.status === 200) {
				displayKeys(JSON.parse(this.responseText).keyItems, obj);
			}
		};
		xhttp.open("GET", '/api/back-manager/keys', true);
		xhttp.send();
	};


	function createKey(obj: any) {
		const xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function() {
			if (this.readyState === 4 && this.status === 201) {
				fetchAndDisplayKeys(obj);
				obj.search = this.responseText;
			}
		};
		xhttp.open("POST", '/api/back-manager/keys', true);

		const request = {
			'user': obj.userCreate,
		};

		xhttp.setRequestHeader('Content-Type', 'application/json');
		xhttp.send(JSON.stringify(request));
	}
</script>

<style>
	.key_table {
		position: fixed;
		bottom: 1vh;
		width: 99vw;
	}
</style>
