use crate::client::Client;
use anyhow::Result;

//- normal : rejoindre un canal en le creant
//- normal : rejoindre un canal existant, avec un user dedans
//
//      Waiting MODE 
//          ERR_INVITEONLYCHAN
//          ERR_BADCHANNELKEY
//          ERR_CHANNELISFULL
//          ERR_TOOMANYTARGETS
//          RPL_JOINED -> la coder nous meme
//          RPL_TOPIC
//
//          ERR_TOOMANYCHANNELS
//

pub async fn join_need_more_params(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("stress_{}", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}_join_more_params\r\n", nick), 0)
        .await?;
    client
        .send(
            &format!(
                "USER {}_join_more_params 0 * :join_need_more_params\r\n",
                nick
            ),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }

    client.send("JOIN \r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :Not enough parameters") {
            return Err(anyhow::anyhow!("Err_NEEDMOREPARAMS missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn join_no_such_channel(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let channel = format!("no_such_chan_{}", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}_join_ns_chan\r\n", channel), 0)
        .await?;
    client
        .send(
            &format!("USER {}_join_ns_chan 0 * :join_ns_chan\r\n", channel),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }

    client.send("JOIN nosuchchannel\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :No such channel") {
            return Err(anyhow::anyhow!("ERR_NOSUCHCHAN missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}


pub async fn join_new_channel(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let channel = format!("{}_join_new_chan", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}_join_new_chan\r\n", channel), 0)
        .await?;
    client
        .send(
            &format!("USER {} 0 * :join_new_chan\r\n", channel),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }

    client.send("JOIN #newchan\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("join_new_chan JOIN #newchan") {
            return Err(anyhow::anyhow!("No confirmation of chan creation | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn join_not_registered(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let channel = format!("{}_join_not_regi", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}_join_not_regi\r\n", channel), 0)
        .await?;

    client.send("JOIN #newchan\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :You have not registered") {
            return Err(anyhow::anyhow!("ERR_NOTREGISTERED missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn join_existing_chan(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let channel = format!("{}_join_exis_chan", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", channel), 0)
        .await?;
    client
        .send(
            &format!("USER {} 0 * :join_new_chan\r\n", channel),
            0,
        )
        .await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }
    client.send("JOIN #newchan\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("JOIN #newchan") {
            return Err(anyhow::anyhow!("Failed to join an existing chan without pw | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn join_existing_multi_chan(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let channel = format!("{}_join_multi", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", channel), 0)
        .await?;
    client
        .send(
            &format!("USER {} 0 * :join_new_chan\r\n", channel),
            0,
        )
        .await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }
    client.send(&format!("JOIN #newchan{},#secondnewchan{}\r\n", id, id), 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(&format!("JOIN #newchan{}", id)) {
            return Err(anyhow::anyhow!("Failed to join first chan | received [{line}]"));
        }
    }
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(&format!("JOIN #secondnewchan{}", id)) {
            return Err(anyhow::anyhow!("Failed to join second chan | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn join_existing_chan_mdp(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let channel = format!("{}_join_mdp_chan", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}_join_mdp_chan\r\n", channel), 0)
        .await?;
    client
        .send(
            &format!("USER {} 0 * :join_new_chan\r\n", channel),
            0,
        )
        .await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }
    client.send("JOIN #mdp_chan chan\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("JOIN #mdp_chan") {
            return Err(anyhow::anyhow!("Failed to join chan_with_mdp | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}




//avec MODE :
// ClientBehavior::JoinInviteOnlyChannel => join_invite_only_channel(port, id, timeout_ms).await,
// ClientBehavior::JoinBadChannelKey => join_bad_channel_key(port, id, timeout_ms).await,
// ClientBehavior::JoinChannelIsFull => join_channel_is_full(port, id, timeout_ms).await,
